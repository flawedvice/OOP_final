/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
public:
  DJAudioPlayer(juce::AudioFormatManager &_formatManager);
  ~DJAudioPlayer();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  void loadURL(juce::URL audioURL);
  void setGain(double gain);
  void setSpeed(double ratio);
  void setPosition(double posInSecs);
  void setPositionRelative(double pos);
  /** Allows user to set track in loop mode indicating if op was successful */
  bool setLooping(bool allowLoop);
  bool getLooping();

  void start();
  void stop();

  /** get the relative position of the playhead */
  double getPositionRelative();

  /** Gets length of song and its progress */
  std::string getTrackProgress();

private:
  juce::AudioFormatManager &formatManager;
  std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
  juce::AudioTransportSource transportSource;
  juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
};
