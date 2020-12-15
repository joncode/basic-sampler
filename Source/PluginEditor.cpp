/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLoadButton.onClick = [&]() { audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    
    setSize (600, 200);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);


    if (mShouldBePainting)
    {
        juce::Path p;
        mAudioPoints.clear();

        auto waveform = audioProcessor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
        
        // scale audio file to window on X-axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        p.startNewSubPath(0, getHeight() / 2);
        
        // scale on Y-axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto scaled_point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, scaled_point);
        }
        
        g.strokePath(p, juce::PathStrokeType(2));
        
        mShouldBePainting = false;
    }

    
//
//    g.setFont(15.0f);
//
//    if (audioProcessor.getNumSamplerSounds() > 0)
//    {
//        g.fillAll(juce::Colours::red);
//        g.drawText("Sound loaded", getWidth() / 2 - 50, getHeight() / 2 - 10 , 100, 20, juce::Justification::centred);
//    }
//    else
//    {
//        g.drawText("Load a sound", getWidth() / 2 - 50, getHeight() / 2 - 10 , 100, 20, juce::Justification::centred);
//    }
}

void HelloSamplerAudioProcessorEditor::resized()
{
//    mLoadButton.setBounds(getWidth() / 2 - 50  , getHeight() / 2 - 50, 100, 100);
}

bool HelloSamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")) {
            return true;
        }
    }
    return false;
}

void HelloSamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files) {
        if (isInterestedInFileDrag(file)) {
            mShouldBePainting = true;
            audioProcessor.loadFile(file);
        }
    }
    
    repaint();
}
