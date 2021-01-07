/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail (p), mADSR(p), audioProcessor (p)
{
    auto tapImage = juce::ImageCache::getFromMemory (BinaryData::tap_png, BinaryData::tap_pngSize);
    
    if (! tapImage.isNull())
        mImageComponent.setImage (tapImage, juce::RectanglePlacement::stretchToFit);
    else
        jassert (! tapImage.isNull());
    
    addAndMakeVisible (mWaveThumbnail);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mImageComponent);
    
    startTimerHz(30);
    
    setSize (600, 400);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void HelloSamplerAudioProcessorEditor::resized()
{
    mWaveThumbnail.setBoundsRelative(0.0f, 0.25f, 1.0f, 0.5f);
    mADSR.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);
    mImageComponent.setBoundsRelative(0.1f, 0.05f, 0.2f, 0.06f);
}

void HelloSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}

