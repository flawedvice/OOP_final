/*
  ==============================================================================

    TrackInfo.cpp
    Created: 7 Mar 2024 11:20:59am
    Author:  vicente

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackInfo.h"

//==============================================================================
TrackInfo::TrackInfo()
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  titleLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
  titleLabel.setFont(14.0f);
  titleLabel.setText("No track selected", juce::NotificationType::dontSendNotification);
  titleLabel.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(titleLabel);
}

TrackInfo::~TrackInfo()
{
}

void TrackInfo::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
     draws some placeholder text to get you started.

     You should replace everything in this method with your own
     drawing code..
  */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::orange);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void TrackInfo::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
  float colW = getWidth() / 3;
  float rowH = getHeight() / 3;
  titleLabel.setBounds(colW, rowH, colW, rowH);
}

void TrackInfo::updateTitle(juce::String title)
{
  if (title.containsNonWhitespaceChars())
  {
    titleLabel.setText(title, juce::NotificationType::dontSendNotification);
  }
}
