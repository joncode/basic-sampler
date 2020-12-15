/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HelloSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor&);
    ~HelloSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton mLoadButton { "Load" };

    HelloSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessorEditor)
};
