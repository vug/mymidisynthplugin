# A side project for learning JUCE

My first goal is to make a simple synth that has following components, where I wrote each of them myself.

- 2 oscillators with 3 types of band-limited waveforms, with detune setting
- A simple filter with freq and resonance parameters
- An ADSR. 
- Maybe a delay effect.
- Maybe tremolo effect. 
- Maybe a vibrato connected to modulation wheel (I don't have a MIDI controller yet though)
- Maybe a pitch-bend input
- Maybe an LFO or ADSR for filter too.

# Active questions
* How to know which modules to include?

# Resources

* Introduction
  * [JUCE \| JUCE](https://juce.com/) JUCE website
  * [Get JUCE \| JUCE](https://shop.juce.com/get-juce) Download framework
  * [Tutorials \| JUCE](https://juce.com/learn/tutorials) Tutorials
* Starting a new project
  * [JUCE: Tutorial: Projucer Part 1: Getting started with the Projucer](https://docs.juce.com/master/tutorial_new_projucer_project.html)
  * [JUCE: Tutorial: Projucer Part 2: Manage your Projucer projects](https://docs.juce.com/master/tutorial_manage_projucer_project.html)
  * [JUCE: Tutorial: Projucer Part 3: Choosing the right Projucer template for your application](https://docs.juce.com/master/tutorial_choosing_projucer_template.html)
* Making noise, setting parameters with slider, stand-alone app
  * [JUCE: Tutorial: Build a white noise generator](https://docs.juce.com/master/tutorial_simple_synth_noise.html)
  * [JUCE: Tutorial: Control audio levels](https://docs.juce.com/master/tutorial_synth_level_control.html)
  * [JUCE: Tutorial: Build a sine wave synthesiser](https://docs.juce.com/master/tutorial_sine_synth.html)
* Plug-in development:
  * Workflow:
    * Build JUCE Plug-In Host and copy its executable to a convenient location
	* Create project files via Projucer
	* Open the project in Visual Studio
	* adjust debugging settings to run JUCE Plug-In Host after every build
	* Debug build the plug-in
	* Open it in JUCE Plug-in Host
	* Connect MIDI inputs to pluging, connect plugin outputs to speakers, adjust block size, add visualization plugins (I added schwa schOPE oscilloscope and spectroscope) and save
	* Change the code, debug build, test in the host
  * [JUCE: Tutorial: Create a basic Audio/MIDI plugin, Part 1: Setting up](https://docs.juce.com/master/tutorial_create_projucer_basic_plugin.html)
  * [Launch AudioPluginHost in Visual Studio for debuging \- JUCE](https://forum.juce.com/t/launch-audiopluginhost-in-visual-studio-for-debuging/30839)
  * [How to set up Visual Studio to use JUCE for debugging? \- JUCE](https://forum.juce.com/t/how-to-set-up-visual-studio-to-use-juce-for-debugging/29660)
  * [JUCE: Tutorial: Create a basic Audio/MIDI plugin, Part 2: Coding your plug\-in](https://docs.juce.com/master/tutorial_code_basic_plugin.html)
  * [What is your plugin development testbench / workflow? \- Audio Plugins \- JUCE](https://forum.juce.com/t/what-is-your-plugin-development-testbench-workflow/13583)
* Monophonic synth key press handling
  * [dictionary \- C\+\+ Help finding the max value in a map \- Stack Overflow](https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map/9371137#9371137)
  * [unordered\_map \- C\+\+ Reference](http://www.cplusplus.com/reference/unordered_map/unordered_map/)
* UI for osc type selection
  * JUCE: Tutorial: The ComboBox class https://docs.juce.com/master/tutorial_combo_box.html
* Parameter (such as volume) change without glitches
  * [JUCE: LinearSmoothedValue< FloatType > Class Template Reference](https://docs.juce.com/master/classLinearSmoothedValue.html#a6cc025f0d2de6ac18dc15368a31e893c)
* Misc
  * [c\+\+ \- Can't use modulus on doubles? \- Stack Overflow](https://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles)
  * [visual studio \- Default directory where new classes are stored? \- Stack Overflow](https://stackoverflow.com/questions/9700170/default-directory-where-new-classes-are-stored)
* JUCE Sliders
  * [JUCE: Slider Class Reference](https://docs.juce.com/master/classSlider.html)
  * [JUCE: Tutorial: The Slider class](https://docs.juce.com/master/tutorial_slider_values.html)
  * [Integer Slider \- General JUCE discussion \- JUCE](https://forum.juce.com/t/integer-slider/26884)
* C++ Math
  * [pow \- C\+\+ Reference](http://www.cplusplus.com/reference/cmath/pow/)
* JUCE Source Control Practices
  * [Having problems with source control \- Audio Plugins \- JUCE](https://forum.juce.com/t/having-problems-with-source-control/19225/3)
  * [JUCE project setup process \| CredlandAudio](http://blog.credland.net/2016/05/juce-project-setup-process.html)
* General Source Control
  * [Whatʼs a Fast Forward Merge?](https://sandofsky.com/images/fast_forward.pdf)
* Adding files to JUCE Project
  * This has to be done trough Projucer. For example, to add a new cpp class file, don't do it using Visual Studio UI. Open "File Explorer" in Projucer. Click on "(+)", then "Add New CPP File..." or if you already had used Visual Studio or something else, "Add Existing Files..."
  * This way, new files will be part of the "JUCE Project" and any IDE export will have them.
  * See: [JUCE: Tutorial: Projucer Part 2: Manage your Projucer projects](https://docs.juce.com/master/tutorial_manage_projucer_project.html)
* Upgrading JUCE
  * I wan't to use the ADSR class that is mentioned in the documentation. Apparently, it was introduced in version 5.4.2, whereas I had version 5.4.1
  * To upgrade the JUCE library, open Projucer. I think it does an "check upgrades" at the beginning. It asks to download newer version. 
  * (I first attempted to download it on the existing folder, however that failed.)
  * Download it to JUCE-5.4.2 folder
  * Open the Projucer in the newer version. Open existing project.
  * File > Global Paths
  * Set "Path to JUCE" and "JUCE Modules" to `C:\Users\veliu\JUCE-5.4.2` paths. 
  * Now when I click on module names in "Modules" section, I see that their version is 5.4.2.
  * Save the Projucer project, and open it in the IDE again "Save an open in IDE".
  * Looks like, module files are not copied to Visual Studio project but their path is known by VS.
  * Build project again, and I must good to go.
* ADSR
  * [JUCE: ADSR Class Reference](https://docs.juce.com/develop/classADSR.html)
  * [JUCE: ADSR::Parameters Struct Reference](https://docs.juce.com/develop/structADSR_1_1Parameters.html)
  * Meaning of ADSR stages [Envelope \(music\) \- Wikipedia](https://en.wikipedia.org/wiki/Envelope_(music))
* C++ Structs
  * [4\.7 — Structs \| Learn C\+\+](https://www.learncpp.com/cpp-tutorial/47-structs/)


