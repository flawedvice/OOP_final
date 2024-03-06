/*
  ==============================================================================

    WaveformDisplay.h
    Created: 6 Mar 2024 11:08:49am
    Author:  vicente

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener
{
public:
  WaveformDisplay(juce::AudioFormatManager &formatManagerToUse,
                  juce::AudioThumbnailCache &cacheToUse);
  ~WaveformDisplay();

  void paint(juce::Graphics &) override;
  void resized() override;

  void changeListenerCallback(juce::ChangeBroadcaster *source) override;

  void loadURL(juce::URL audioURL);

  /** set the relative position of the playhead*/
  void setPositionRelative(double pos);

private:
  juce::AudioThumbnail audioThumb;
  bool fileLoaded;
  double position;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
