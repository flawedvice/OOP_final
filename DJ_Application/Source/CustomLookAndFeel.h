/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 6 Mar 2024 3:42:02pm
    Author:  vicente

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
  CustomLookAndFeel();
  /**
   * Used to style Knob sliders.
   */
  void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &) override;
};
