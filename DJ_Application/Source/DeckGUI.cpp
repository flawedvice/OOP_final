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
    trackTitle.addListener(this);
    trackTitle.setFont(14.0f);
    trackTitle.setJustificationType(juce::Justification::centred);
    trackTitle.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
    trackTitle.setText("No track selected", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(trackTitle);

    trackProgress.setFont(14.0f);
    trackProgress.setJustificationType(juce::Justification::centredTop);
    trackProgress.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
    trackProgress.setText("00:00 / 00:00", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(trackProgress);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    loopButton.addListener(this);

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loopButton);

    addAndMakeVisible(playlistComponent);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    volSlider.setLookAndFeel(&customLook);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    speedSlider.setLookAndFeel(&customLook);
    speedSlider.setSliderStyle(juce::Slider::Rotary);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

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
}

void DeckGUI::resized()
{
    double yMargin = getHeight() / 14;
    double xMargin = getWidth() / 16;
    double rowH = getHeight() / 8;
    double colW = getWidth() / 6;

    trackTitle.setBounds(colW - xMargin, rowH - yMargin, colW * 3, rowH);
    trackProgress.setBounds(colW - xMargin, rowH * 2 - yMargin, colW * 3, rowH);
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
                                 waveformDisplay.loadURL(juce::URL{chooser.getResult()});
                                 // Display the track's title
                                 trackTitle.setText(chooser.getResult().getFileNameWithoutExtension(), juce::NotificationType::sendNotification); });
    }
    if (button == &loopButton)
    {
        bool isLooping = player->getLooping();
        if (isLooping)
        {
            bool success = player->setLooping(false);
            if (success)
            {
                button->setButtonText("Not looping");
            }
        }
        else
        {
            bool success = player->setLooping(true);
            if (success)
            {
                button->setButtonText("Looping");
            }
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

void DeckGUI::labelTextChanged(juce::Label *labelThatHasChanged)
{
    std::cout << "Track changed: " << labelThatHasChanged->getText() << std::endl;
    if (labelThatHasChanged == &trackTitle && trackTitle.getText() != "No track selected")
    {
        player->start();
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
        // Display the track's title
        trackTitle.setText(juce::File{files[0]}.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
    }
}

void DeckGUI::timerCallback()
{
    // std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
    if (trackTitle.getText() != "No track selected")
    {
        trackProgress.setText(player->getTrackProgress(), juce::NotificationType::dontSendNotification);
    }
}
