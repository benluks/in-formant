#include "contextmanager.h"
#include "contextbuilder.h"
#include "../synthesis/synthesis.h"

#include <iostream>
#include <thread>

using namespace Main;
using namespace std::chrono;
using namespace std::chrono_literals;
using Clock = steady_clock;

ContextManager::ContextManager(std::unique_ptr<Context>&& ctx)
    : ctx(std::move(ctx)),
      pipeline(this->ctx->captureBuffer.get())
{}

void ContextManager::initialize()
{
    ctx->audio->initialize();
    ctx->audio->refreshDevices();

    durProcessing = 0us;
    durRendering = 0us;
    durLoop = 0us;
}

void ContextManager::start()
{
    loadSettings();
    
    ctx->audio->openCaptureStream(nullptr);
    ctx->audio->startCaptureStream();

    updateNodeParameters();
    pipeline.initialize();

    endLoop = false;
    isPaused = false;
  
    while (!endLoop) {
        mainBody();
        // Locked to ~60 fps
        if (durLoop < 16.67ms) {
            std::this_thread::sleep_for(16.67ms - durLoop);
        }
    }
}

void ContextManager::terminate()
{
    ctx->audio->stopCaptureStream();
    ctx->audio->closeCaptureStream();

    ctx->audio->terminate();
}

void ContextManager::loadSettings()
{
    outputGain = 0;
    
    analysisDuration = 35;
    analysisMaxFrequency = 4000;

    viewMinFrequency = 1;
    viewMaxFrequency = 6000;
    viewMinGain = -80;
    viewMaxGain = +0;

    fftLength = 2048;
    fftMaxFrequency = viewMaxFrequency;

    preEmphasisFrequency = 200.0f;
    
    pitchAndLpSampleRate = 32'000;

    linPredOrder = 8;
    linPredOrderOffset = +2;

    spectrogramCount = 400;

    spectrogramTrack.resize(spectrogramCount);
    lpSpecTrack.resize(spectrogramCount);
    pitchTrack.resize(spectrogramCount);
    formantTrack.resize(spectrogramCount);
    soundTrack.resize(spectrogramCount);
    glotTrack.resize(spectrogramCount);
    glotInstTrack.resize(spectrogramCount);
}

void ContextManager::updateNodeParameters()
{
    fftMaxFrequency = viewMaxFrequency;

    pipeline.setPitchSolver(ctx->pitchSolver.get());
    pipeline.setInvglotSolver(ctx->invglotSolver.get());
    pipeline.setLinpredSolver(ctx->linpredSolver.get());
    pipeline.setFormantSolver(ctx->formantSolver.get());

    pipeline.setAnalysisDuration(milliseconds(analysisDuration));

    pipeline.setFFTSampleRate(2 * fftMaxFrequency);
    pipeline.setFFTSize(fftLength);

    pipeline.setPitchAndLpSpectrumSampleRate(pitchAndLpSampleRate);

    pipeline.setFormantSampleRate(2 * analysisMaxFrequency);
    pipeline.setFormantLpOrder(linPredOrder);
}

void ContextManager::updateWithNextFrame()
{
    spectrogramTrack.pop_front();
    spectrogramTrack.push_back(pipeline.getFFTSlice());

    lpSpecTrack.pop_front();
    lpSpecTrack.push_back(pipeline.getLpSpectrumSlice());

    pitchTrack.pop_front();
    pitchTrack.push_back(pipeline.getPitch());

    formantTrack.pop_front();
    formantTrack.push_back(pipeline.getFormants());

    soundTrack.pop_front();
    soundTrack.push_back(pipeline.getSound());

    glotTrack.pop_front();
    glotTrack.push_back(pipeline.getGlottalFlow());

    glotInstTrack.pop_front();
    glotInstTrack.push_back(pipeline.getGlottalInstants());
}

void ContextManager::mainBody(bool processEvents)
{
    auto t0 = Clock::now();

    if (processEvents) {

        if (endLoop) return;
    
        if (ctx->audio->needsTicking()) {
            ctx->audio->tickAudio();
        }

        if (!isPaused) {
            pipeline.processAll();
            updateWithNextFrame();
        }

        auto tr0 = Clock::now();
        auto tr1 = Clock::now();

        durRendering = duration_cast<microseconds>(tr1 - tr0);
        auto t1 = Clock::now();

        durLoop = duration_cast<microseconds>(t1 - t0);
    }
}
