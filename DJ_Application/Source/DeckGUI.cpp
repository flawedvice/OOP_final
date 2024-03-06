/*
  ==============================================================================

    DeckGUI.cpp
    Created: 11 Feb 2024 10:34:42am
    Author:  vicente

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer *_player) : player(_player)
{
  addAndMakeVisible(playButton);
  addAndMakeVisible(stopButton);
  addAndMakeVisible(loadButton);

  addAndMakeVisible(volumeSlider);
  addAndMakeVisible(positionSlider);
  addAndMakeVisible(speedSlider);

  playButton.addListener(this);
  stopButton.addListener(this);
  loadButton.addListener(this);

  volumeSlider.addListener(this);
  positionSlider.addListener(this);
  speedSlider.addListener(this);

  volumeSlider.setRange(0.0, 1.0);
  positionSlider.setRange(0.0, 1.0);
  speedSlider.setRange(0.0, 100.0);
}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint(juce::Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void DeckGUI::resized()
{
  float rowH = getHeight() / 6;
  playButton.setBounds(0, 0, getWidth(), rowH);
  stopButton.setBounds(0, rowH, getWidth(), rowH);
  volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
  positionSlider.setBounds(0, rowH * 3, getWidth(), rowH);
  speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
  loadButton.setBounds(0, rowH * 5, getWidth(), rowH);
}

void DeckGUI::buttonClicked(juce::Button *button)
{
  if (button == &playButton)
  {
    player->play();
  }
  else if (button == &stopButton)
  {
    player->stop();
  }
  else if (button == &loadButton)
  {
    std::cout << "Load btn!" << std::endl;

    chooser = std::make_unique<juce::FileChooser>("Select a WAV file to play...", juce::File{}, "*.wav;*.mp3");

    auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser &chooser)
                         {
            std::cout << "Opened chooser!" << std::endl;
            auto file = chooser.getResult();
            if (file != juce::File{})
            {
                std::cout << "Chose file: " << file.getFileName() << std::endl;

                juce::URL audioURL = juce::URL{chooser.getResult()};
                player->loadURL(audioURL);
            } });
  }
}

void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
  if (slider == &volumeSlider)
  {
    player->setGain(slider->getValue());
  }
  if (slider == &speedSlider)
  {
    player->setSpeed(slider->getValue());
  }
  if (slider == &positionSlider)
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
  for (juce::String filename : files)
  {
    std::cout << "DeckGUI::filesDropped " << filename << std::endl;
    juce::URL fileURL = juce::URL{juce::File{filename}};
    player->loadURL(fileURL);
    return;
  }
}