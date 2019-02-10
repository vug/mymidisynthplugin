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
* Parameter (such as volume) change without glitches
  * [JUCE: LinearSmoothedValue< FloatType > Class Template Reference](https://docs.juce.com/master/classLinearSmoothedValue.html#a6cc025f0d2de6ac18dc15368a31e893c)
* Misc
  * [c\+\+ \- Can't use modulus on doubles? \- Stack Overflow](https://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles)
  * [visual studio \- Default directory where new classes are stored? \- Stack Overflow](https://stackoverflow.com/questions/9700170/default-directory-where-new-classes-are-stored)
* JUCE Source Control Practices
  * [Having problems with source control \- Audio Plugins \- JUCE](https://forum.juce.com/t/having-problems-with-source-control/19225/3)
  * [JUCE project setup process \| CredlandAudio](http://blog.credland.net/2016/05/juce-project-setup-process.html)

