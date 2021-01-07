/*
  ==============================================================================

    ADSRComponent.h
    Created: 7 Jan 2021 2:30:31pm
    Author:  Jon Barber

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent(HelloSamplerAudioProcessor& p);
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;

    HelloSamplerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
