/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/*
 */
class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::Label::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
  DeckGUI(DJAudioPlayer *player,
          juce::AudioFormatManager &formatManagerToUse,
          juce::AudioThumbnailCache &cacheToUse);
  ~DeckGUI();

  void paint(juce::Graphics &) override;
  void resized() override;

  /** implement Button::Listener */
  void buttonClicked(juce::Button *) override;

  /** implement Slider::Listener */
  void sliderValueChanged(juce::Slider *slider) override;

  /** Listen to Label text changes*/
  void labelTextChanged(juce::Label *labelThatHasChanged);

  bool isInterestedInFileDrag(const juce::StringArray &files) override;
  void filesDropped(const juce::StringArray &files, int x, int y) override;

  void timerCallback() override;

private:
  juce::Label trackTitle;
  juce::Label trackProgress;

  juce::TextButton playButton{"Play"};
  juce::TextButton stopButton{"Stop"};
  juce::TextButton loadButton{"Load"};
  juce::TextButton loopButton{"Not looping"};

  juce::Slider volSlider;
  juce::Slider speedSlider;
  juce::Slider posSlider;

  juce::FileChooser fChooser{"Select a file...", juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("tracks")};

  WaveformDisplay waveformDisplay;

  DJAudioPlayer *player;

  PlaylistComponent playlistComponent;

  CustomLookAndFeel customLook;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
