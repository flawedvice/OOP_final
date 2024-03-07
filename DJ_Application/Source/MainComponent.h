/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent,
                      public juce::KeyListener
{
public:
  //==============================================================================
  MainComponent();
  ~MainComponent();

  //==============================================================================
  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  //==============================================================================
  void paint(juce::Graphics &g) override;
  void resized() override;
  //==============================================================================

  /** Key Press Listener to close the application */
  bool keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent) override;

private:
  //==============================================================================
  // Your private member variables go here...

  juce::AudioFormatManager formatManager;
  juce::AudioThumbnailCache thumbCache{100};

  DJAudioPlayer player1{formatManager};
  DeckGUI deckGUI1{&player1, formatManager, thumbCache};

  DJAudioPlayer player2{formatManager};
  DeckGUI deckGUI2{&player2, formatManager, thumbCache};

  juce::MixerAudioSource mixerSource;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
