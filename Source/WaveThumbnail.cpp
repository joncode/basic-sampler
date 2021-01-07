/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 22 Dec 2020 12:36:37am
    Author:  Jon Barber

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail (HelloSamplerAudioProcessor& p) : audioProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::cadetblue.darker());
    
    auto waveform = audioProcessor.getWaveForm();
    
    if (waveform.getNumSamples() > 0)
    {
        juce::Path pa;
        mAudioPoints.clear();

        
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
        
        // scale audio file to window on X-axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        g.setColour (juce::Colours::yellow);
        pa.startNewSubPath(0, getHeight() / 2);
        
        // scale on Y-axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto scaled_point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            pa.lineTo(sample, scaled_point);
        }
        
        g.strokePath(pa, juce::PathStrokeType(2));
        
        g.setColour(juce::Colours::white);
        g.setFont (15.0f);
        auto textBounds = getLocalBounds().reduced(10, 10);
        g.drawFittedText(mFileName, textBounds, juce::Justification::topRight, 1);
        
    } else
    {
        g.setColour(juce::Colours::white);
        g.setFont (40.0f);
        g.drawFittedText("Drop an Audio File to load", getLocalBounds(), juce::Justification::centred, 1);
    }


}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool WaveThumbnail::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")) {
            return true;
        }
    }
    return false;
}

void WaveThumbnail::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files) {
        if (isInterestedInFileDrag(file))
        {
            auto myFile = std::make_unique<juce::File> (file);
            mFileName = myFile->getFileNameWithoutExtension();
            
            audioProcessor.loadFile(file);
        }
    }
    
    repaint();
}
