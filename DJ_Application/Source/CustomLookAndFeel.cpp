/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 6 Mar 2024 3:42:02pm
    Author:  vicente

  ==============================================================================
*/

#include "CustomLookAndFeel.h"
#include <JuceHeader.h>

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                                         const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &)
{
  float radius = juce::jmin(width / 2, height / 2) - 4.0f;
  float centreX = x + width * 0.5f;
  float centreY = y + height * 0.5f;
  float rx = centreX - radius;
  float ry = centreY - radius;
  float rw = radius * 2.0f;
  float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

  // Fill the Knob
  g.setColour(juce::Colours::grey);
  g.fillEllipse(rx, ry, rw, rw);

  // Set an outline
  g.setColour(juce::Colours::darkgrey);
  g.drawEllipse(rx, ry, rw, rw, 0.2f);

  // Set the Pointer of the Knob
  juce::Path knobPointer;
  float pointerLength = radius;
  float pointerThickness = 4.0f;
  knobPointer.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
  knobPointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

  // Style the previous Pointer
  g.setColour(juce::Colours::darkgrey);
  g.fillPath(knobPointer);
}
