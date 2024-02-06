#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio) && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                          [&](bool granted)
                                          { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setButtonText("LOAD");

    gainSlider.setRange(0, 1);

    formatManager.registerBasicFormats();
    for (int i = 0; i < formatManager.getNumKnownFormats(); i++)
    {
        std::string s =
            formatManager.getKnownFormat(i)->getFormatName().toStdString();
        std::cout << i << " " << s << std::endl;
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    playing = false;
    gain = 0.5;
    phase = 0;
    dphase = 0;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    // Your audio-processing code goes here!

    if (!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    playButton.setBounds(0, 0, getWidth(), getHeight() / 5);
    stopButton.setBounds(0, getHeight() / 5, getWidth(), getHeight() / 5);
    loadButton.setBounds(0, getHeight() / 5 * 2, getWidth(), getHeight() / 5);
    gainSlider.setBounds(0, getHeight() / 5 * 3, getWidth(), getHeight() / 5);
}

void MainComponent::buttonClicked(juce::Button *button)
{
    if (button == &playButton)
    {
        playing = true;
        dphase = 0;
        transportSource.setPosition(0);
        transportSource.start();
    }
    else if (button == &stopButton)
    {
        playing = false;
        transportSource.stop();
    }
    else if (button == &loadButton)
    {
        // - configure the dialogue
        auto fileChooserFlags =
            juce::FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that
        // but it is necessary as of JUCE 6.1
        fChooser.launchAsync(fileChooserFlags,
                             [this](const juce::FileChooser &chooser)
                             {
                                 auto chosenFile = chooser.getResult();
                                 loadURL(juce::URL{chosenFile});
                             });
    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainSlider)
    {
        std::cout << gainSlider.getValue() << std::endl;
        gain = gainSlider.getValue();
        transportSource.setGain(gain);
    }
}

void MainComponent::loadURL(juce::URL audioURL)
{
    auto *reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
    else
    {
        std::cout << "Something went wrong loading the file " << std::endl;
    }
}