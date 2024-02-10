/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 9 Feb 2024 8:24:36am
    Author:  vicente

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource
{
public:
  DJAudioPlayer();
  ~DJAudioPlayer();

  // Implement virtual methods from juce::AudioSource
  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  /** Loads audio file from URI/URL */
  void loadURL(juce::URL audioURL);
  /** Sets gain of the reproduction */
  void setGain(double gain);
  void setSpeed(double ratio);
  /** Sets position of reproducer in seconds */
  void setPosition(double posInSecs);
  void setPositionRelative(double pos);

  /** Starts playing the file */
  void play();
  /** Stops playing the file */
  void stop();

private:
  juce::AudioFormatManager formatManager;
  std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
  juce::AudioTransportSource transportSource;
  juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
};