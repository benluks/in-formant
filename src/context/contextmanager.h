#ifndef MAIN_CONTEXT_MANAGER_H
#define MAIN_CONTEXT_MANAGER_H

#include "context.h"
#include "../nodes/nodes.h"
#include "../modules/app/app.h"

#include <unordered_map>
#include <memory>
#include <vector>

namespace Main {

    using namespace Module;

    class ContextManager {
    public:
        ContextManager(std::unique_ptr<Context>&& ctx);

        void initialize();
        void start();
        void terminate();

    private:
        void loadSettings();

        void updateNodeParameters();
        void updateWithNextFrame();

        void mainBody(bool processEvents = true);

        std::unique_ptr<Context> ctx;
        App::Pipeline pipeline;

        bool endLoop;
        bool isPaused;
        bool displayLpSpec;
        bool useFrameCursor;
        bool isNoiseOn;
        bool displayFormantTracks;
        bool displayLegends;

        float outputGain;
            
        int analysisDuration;
        int analysisMaxFrequency;

        int fftLength;
        int fftMaxFrequency;

        int preEmphasisFrequency;
        int pitchAndLpSampleRate;
        int linPredOrder;
        int linPredOrderOffset;

        int spectrogramCount;

        std::deque<std::vector<std::array<float, 2>>>  spectrogramTrack;
        std::deque<std::vector<std::array<float, 2>>>  lpSpecTrack;
        std::deque<float>                              pitchTrack;
        std::deque<std::vector<Analysis::FormantData>> formantTrack;
        std::deque<std::vector<float>>                 soundTrack;
        std::deque<std::vector<float>>                 glotTrack;
        std::deque<std::vector<float>>                 glotInstTrack;

        std::chrono::microseconds durProcessing;
        std::chrono::microseconds durRendering;
        std::chrono::microseconds durLoop;
    };    
}

#endif // MAIN_CONTEXT_MANAGER_H
