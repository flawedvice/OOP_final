/*
  ==============================================================================

    TrackInfo.h
    Created: 7 Mar 2024 11:20:59am
    Author:  vicente

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class TrackInfo : public juce::Component
{
public:
  TrackInfo();
  ~TrackInfo() override;

  void paint(juce::Graphics &) override;
  void resized() override;

  void updateTitle(juce::String title);

private:
  juce::Label titleLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackInfo)
};
