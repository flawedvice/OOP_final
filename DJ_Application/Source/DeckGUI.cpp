/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 juce::AudioFormatManager &formatManagerToUse,
                 juce::AudioThumbnailCache &cacheToUse) : player(_player),
                                                          waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(waveformDisplay);

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loopButton);

    addAndMakeVisible(playlistComponent);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    volSlider.setLookAndFeel(&customLook);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    speedSlider.setLookAndFeel(&customLook);
    speedSlider.setSliderStyle(juce::Slider::Rotary);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    loopButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics &g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("DeckGUI", getLocalBounds(),
               juce::Justification::centred, true); // draw some placeholder text
}

void DeckGUI::resized()
{
    double yMargin = getHeight() / 14;
    double xMargin = getWidth() / 16;
    double rowH = getHeight() / 8;
    double colW = getWidth() / 6;

    posSlider.setBounds(colW - xMargin, rowH * 3 - yMargin, colW * 3, rowH);
    waveformDisplay.setBounds(colW - xMargin, rowH * 4 - yMargin, colW * 3, rowH);
    loadButton.setBounds(colW - xMargin, rowH * 5 - yMargin, colW, rowH);
    playButton.setBounds(colW * 2 - xMargin, rowH * 5 - yMargin, colW, rowH);
    stopButton.setBounds(colW * 3 - xMargin, rowH * 5 - yMargin, colW, rowH);
    playlistComponent.setBounds(colW - xMargin, rowH * 6 - yMargin, colW * 3, rowH * 2);
    loopButton.setBounds(colW * 5 - xMargin, rowH * 2 - yMargin, colW, rowH);
    speedSlider.setBounds(colW * 5 - xMargin, rowH * 3 - yMargin, colW, rowH);
    volSlider.setBounds(colW * 5 - xMargin, rowH * 4 - yMargin, colW, rowH * 4);
}

void DeckGUI::buttonClicked(juce::Button *button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags =
            juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser &chooser)
                             {
            player->loadURL(juce::URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(juce::URL{chooser.getResult()}); });
    }
    if (button == &loopButton)
    {
        bool isLooping = player->getLooping();
        if (isLooping)
        {
            player->setLooping(false);
            button->setButtonText("Not looping");
        }
        else
        {
            player->setLooping(true);
            button->setButtonText("Looping");
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    // std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
}
