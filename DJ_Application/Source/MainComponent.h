#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    //==============================================================================
    // Own methods
    void buttonClicked(Button* button);
    void sliderValueChanged(Slider* slider);

private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::TextButton playButton;
    juce::TextButton stopButton;
    Random random;
    bool playing;
    double gain;
    juce::Slider gainSlider;
    float phase;
    double dphase;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
