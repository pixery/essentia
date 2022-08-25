#include "algorithmfactory.h"
#include "algorithms/complex/cartesiantopolar.h"
#include "algorithms/standard/scale.h"
#include "algorithms/standard/fftkcomplex.h"
#include "algorithms/standard/fftk.h"
#include "algorithms/standard/framecutter.h"
#include "algorithms/standard/noiseadder.h"
#include "algorithms/standard/windowing.h"
#include "algorithms/rhythm/onsetdetectionglobal.h"
#include "algorithms/rhythm/beattrackermultifeature.h"
#include "algorithms/rhythm/beattrackerdegara.h"
#include "algorithms/rhythm/rhythmextractor2013.h"
#include "algorithms/rhythm/tempotapdegara.h"
#include "algorithms/rhythm/onsetdetection.h"
#include "algorithms/spectral/hfc.h"
#include "algorithms/spectral/flux.h"
#include "algorithms/spectral/melbands.h"
#include "algorithms/spectral/triangularbands.h"
#include "algorithms/filters/movingaverage.h"
#include "algorithms/standard/autocorrelation.h"
#include "algorithms/standard/ifftk.h"
#include "algorithms/filters/iir.h"
#include "algorithms/spectral/erbbands.h"
#include "algorithms/complex/magnitude.h"
#include "algorithms/standard/spectrum.h"
#include "algorithms/rhythm/tempotapmaxagreement.h"
#include "algorithms/rhythm/onsetrate.h"
#include "algorithms/rhythm/onsets.h"

namespace essentia {
    namespace standard {

        ESSENTIA_API void registerAlgorithm() {
            // Filters Begin
            AlgorithmFactory::Registrar<MovingAverage> regMovingAverage;
            AlgorithmFactory::Registrar<IIR> regIIR;
            // Filters End

            // Spectral Begin
            AlgorithmFactory::Registrar<Flux> regFlux;
            AlgorithmFactory::Registrar<HFC> regHFC;
            AlgorithmFactory::Registrar<MelBands> regMelBands;
            AlgorithmFactory::Registrar<TriangularBands> regTriangularBands;
            AlgorithmFactory::Registrar<ERBBands> regERBBands;
            // Spectral End

            AlgorithmFactory::Registrar<CartesianToPolar> regCartesianToPolar;
            AlgorithmFactory::Registrar<Magnitude> regMagnitude;
            AlgorithmFactory::Registrar<Scale> regScale;
            AlgorithmFactory::Registrar<FFTKComplex> regFFTKComplex;
            AlgorithmFactory::Registrar<FFTK> regFFTK;
            AlgorithmFactory::Registrar<IFFTK> regIFFTK;
            AlgorithmFactory::Registrar<FrameCutter> regFrameCutter;
            AlgorithmFactory::Registrar<Spectrum> regSpectrum;
            AlgorithmFactory::Registrar<AutoCorrelation> regAutoCorrelation;
            AlgorithmFactory::Registrar<NoiseAdder> regNoiseAdder;
            AlgorithmFactory::Registrar<Windowing> regWindowing;
            AlgorithmFactory::Registrar<OnsetDetectionGlobal> regOnsetDetectionGlobal;
            AlgorithmFactory::Registrar<BeatTrackerMultiFeature> regBeatTrackerMultiFeature;
            AlgorithmFactory::Registrar<BeatTrackerDegara> regBeatTrackerDegara;
            AlgorithmFactory::Registrar<RhythmExtractor2013> regRhythmExtractor2013;
            AlgorithmFactory::Registrar<TempoTapDegara> regTempoTapDegara;
            AlgorithmFactory::Registrar<OnsetDetection> regOnsetDetection;
            AlgorithmFactory::Registrar<TempoTapMaxAgreement> regTempoTagMaxAgreement;
            AlgorithmFactory::Registrar<OnsetRate> regOnsetRate;
            AlgorithmFactory::Registrar<Onsets> regOnsets;
        }}}



namespace essentia {
    namespace streaming {

        ESSENTIA_API void registerAlgorithm() {
            // Filters Begin
            AlgorithmFactory::Registrar<MovingAverage, essentia::standard::MovingAverage> regMovingAverage;
            AlgorithmFactory::Registrar<IIR, essentia::standard::IIR> regIIR;
            // Filters End

            // Spectral Begin
            AlgorithmFactory::Registrar<Flux, essentia::standard::Flux> regFlux;
            AlgorithmFactory::Registrar<HFC, essentia::standard::HFC> regHFC;
            AlgorithmFactory::Registrar<MelBands, essentia::standard::MelBands> regMelBands;
            AlgorithmFactory::Registrar<TriangularBands, essentia::standard::TriangularBands> regTriangularBands;
            AlgorithmFactory::Registrar<ERBBands, essentia::standard::ERBBands> regERBBands;
            // Spectral End

            AlgorithmFactory::Registrar<CartesianToPolar, essentia::standard::CartesianToPolar> regCartesianToPolar;
            AlgorithmFactory::Registrar<Magnitude, essentia::standard::Magnitude> regMagnitude;
            AlgorithmFactory::Registrar<Scale, essentia::standard::Scale> regScale;
            AlgorithmFactory::Registrar<FFTKComplex, essentia::standard::FFTKComplex> regFFTKComplex;
            AlgorithmFactory::Registrar<FFTK, essentia::standard::FFTK> regFFTK;
            AlgorithmFactory::Registrar<IFFTK, essentia::standard::IFFTK> regIFFTK;
            AlgorithmFactory::Registrar<FrameCutter, essentia::standard::FrameCutter> regFrameCutter;
            AlgorithmFactory::Registrar<Spectrum, essentia::standard::Spectrum> regSpectrum;
            AlgorithmFactory::Registrar<AutoCorrelation, essentia::standard::AutoCorrelation> regAutoCorrelation;
            AlgorithmFactory::Registrar<NoiseAdder, essentia::standard::NoiseAdder> regNoiseAdder;
            AlgorithmFactory::Registrar<Windowing, essentia::standard::Windowing> regWindowing;
            AlgorithmFactory::Registrar<OnsetDetectionGlobal, essentia::standard::OnsetDetectionGlobal> regOnsetDetectionGlobal;
            AlgorithmFactory::Registrar<BeatTrackerMultiFeature, essentia::standard::BeatTrackerMultiFeature> regBeatTrackerMultiFeature;
            AlgorithmFactory::Registrar<BeatTrackerDegara, essentia::standard::BeatTrackerDegara> regBeatTrackerDegara;
            AlgorithmFactory::Registrar<RhythmExtractor2013, essentia::standard::RhythmExtractor2013> regRhythmExtractor2013;
            AlgorithmFactory::Registrar<TempoTapDegara, essentia::standard::TempoTapDegara> regTempoTapDegara;
            AlgorithmFactory::Registrar<OnsetDetection, essentia::standard::OnsetDetection> regOnsetDetection;
            AlgorithmFactory::Registrar<TempoTapMaxAgreement, essentia::standard::TempoTapMaxAgreement> regTempoTagMaxAgreement;
            AlgorithmFactory::Registrar<OnsetRate, essentia::standard::OnsetRate> regOnsetRate;
            AlgorithmFactory::Registrar<Onsets, essentia::standard::Onsets> regOnsets;
        }}}
