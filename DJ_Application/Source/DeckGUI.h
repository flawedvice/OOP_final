/*
  ==============================================================================

    DeckGUI.h
    Created: 11 Feb 2024 10:34:42am
    Author:  vicente

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
 */
class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget
{
public:
  DeckGUI(DJAudioPlayer *player);
  ~DeckGUI() override;

  void paint(juce::Graphics &) override;
  void resized() override;

  void buttonClicked(juce::Button *button);
  void sliderValueChanged(juce::Slider *slider);

  bool isInterestedInFileDrag(const juce::StringArray &files) override;
  void filesDropped(const juce::StringArray &files, int x, int y) override;

private:
  juce::TextButton playButton{"PLAY"};
  juce::TextButton stopButton{"STOP"};
  juce::TextButton loadButton{"LOAD"};

  juce::Slider volumeSlider;
  juce::Slider positionSlider;
  juce::Slider speedSlider;

  DJAudioPlayer *player;

  std::unique_ptr<juce::FileChooser> chooser;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
