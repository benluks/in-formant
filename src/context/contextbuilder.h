#ifndef MAIN_CONTEXT_BUILDER_H
#define MAIN_CONTEXT_BUILDER_H

#include <sstream>

#include "context.h"

namespace Main {

    using namespace Module;

    template <typename AudioType>
    class ContextBuilder {
    public:
        std::unique_ptr<Context> build() {
            auto ctx = std::make_unique<Context>();
    
            ctx->audio = std::make_unique<AudioType>();

            ctx->captureBuffer = std::make_unique<Audio::Buffer>(
                    captureSampleRate, captureDuration);

            ctx->audio->setCaptureBuffer(ctx->captureBuffer.get());

            ctx->pitchSolver.reset(pitchSolver);
            ctx->linpredSolver.reset(linpredSolver);
            ctx->formantSolver.reset(formantSolver);
            ctx->invglotSolver.reset(invglotSolver);
            
            return ctx;
        }

        ContextBuilder& setPitchSolver(Analysis::PitchSolver *o) {
            pitchSolver = o;
            return *this;
        }

        ContextBuilder& setLinpredSolver(Analysis::LinpredSolver *o) {
            linpredSolver = o;
            return *this;
        }

        ContextBuilder& setFormantSolver(Analysis::FormantSolver *o) {
            formantSolver = o;
            return *this;
        }

        ContextBuilder& setInvglotSolver(Analysis::InvglotSolver *o) {
            invglotSolver = o;
            return *this;
        }

        ContextBuilder& setCaptureSampleRate(int o) {
            captureSampleRate = o;
            return *this;
        }

        ContextBuilder& setCaptureDuration(const std::chrono::milliseconds& o) {
            captureDuration = o.count();
            return *this;
        }

    private:
        Analysis::PitchSolver   *pitchSolver;
        Analysis::LinpredSolver *linpredSolver;
        Analysis::FormantSolver *formantSolver;
        Analysis::InvglotSolver *invglotSolver;
        int captureSampleRate;
        int captureDuration;
    };

}

#endif // MAIN_CONTEXT_BUILDER_H
