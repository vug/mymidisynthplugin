/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"\xef\xbb\xbf# A side project for learning JUCE\r\n"
"\r\n"
"My first goal is to make a simple synth that has following components, where I wrote each of them myself.\r\n"
"\r\n"
"- 2 oscillators with 3 types of band-limited waveforms, with detune setting\r\n"
"- A simple filter with freq and resonance parameters\r\n"
"- An ADSR. \r\n"
"- Maybe a delay effect.\r\n"
"- Maybe tremolo effect. \r\n"
"- Maybe a vibrato connected to modulation wheel (I don't have a MIDI controller yet though)\r\n"
"- Maybe a pitch-bend input\r\n"
"- Maybe an LFO or ADSR for filter too.\r\n"
"\r\n"
"# Active questions\r\n"
"* How to know which modules to include?\r\n"
"\r\n"
"# Resources\r\n"
"\r\n"
"* Introduction\r\n"
"  * [JUCE \\| JUCE](https://juce.com/) JUCE website\r\n"
"  * [Get JUCE \\| JUCE](https://shop.juce.com/get-juce) Download framework\r\n"
"  * [Tutorials \\| JUCE](https://juce.com/learn/tutorials) Tutorials\r\n"
"* Starting a new project\r\n"
"  * [JUCE: Tutorial: Projucer Part 1: Getting started with the Projucer](https://docs.juce.com/master/tutorial_new_projucer_project.html)\r\n"
"  * [JUCE: Tutorial: Projucer Part 2: Manage your Projucer projects](https://docs.juce.com/master/tutorial_manage_projucer_project.html)\r\n"
"  * [JUCE: Tutorial: Projucer Part 3: Choosing the right Projucer template for your application](https://docs.juce.com/master/tutorial_choosing_projucer_template.html)\r\n"
"* Making noise, setting parameters with slider, stand-alone app\r\n"
"  * [JUCE: Tutorial: Build a white noise generator](https://docs.juce.com/master/tutorial_simple_synth_noise.html)\r\n"
"  * [JUCE: Tutorial: Control audio levels](https://docs.juce.com/master/tutorial_synth_level_control.html)\r\n"
"  * [JUCE: Tutorial: Build a sine wave synthesiser](https://docs.juce.com/master/tutorial_sine_synth.html)\r\n"
"* Plug-in development:\r\n"
"  * Workflow:\r\n"
"    * Build JUCE Plug-In Host and copy its executable to a convenient location\r\n"
"\t* Create project files via Projucer\r\n"
"\t* Open the project in Visual Studio\r\n"
"\t* adjust debugging settings to run JUCE Plug-In Host after every build\r\n"
"\t* Debug build the plug-in\r\n"
"\t* Open it in JUCE Plug-in Host\r\n"
"\t* Connect MIDI inputs to pluging, connect plugin outputs to speakers, adjust block size, add visualization plugins (I added schwa schOPE oscilloscope and spectroscope) and save\r\n"
"\t* Change the code, debug build, test in the host\r\n"
"  * [JUCE: Tutorial: Create a basic Audio/MIDI plugin, Part 1: Setting up](https://docs.juce.com/master/tutorial_create_projucer_basic_plugin.html)\r\n"
"  * [Launch AudioPluginHost in Visual Studio for debuging \\- JUCE](https://forum.juce.com/t/launch-audiopluginhost-in-visual-studio-for-debuging/30839)\r\n"
"  * [How to set up Visual Studio to use JUCE for debugging? \\- JUCE](https://forum.juce.com/t/how-to-set-up-visual-studio-to-use-juce-for-debugging/29660)\r\n"
"  * [JUCE: Tutorial: Create a basic Audio/MIDI plugin, Part 2: Coding your plug\\-in](https://docs.juce.com/master/tutorial_code_basic_plugin.html)\r\n"
"  * [What is your plugin development testbench / workflow? \\- Audio Plugins \\- JUCE](https://forum.juce.com/t/what-is-your-plugin-development-testbench-workflow/13583)\r\n"
"* Monophonic synth key press handling\r\n"
"  * [dictionary \\- C\\+\\+ Help finding the max value in a map \\- Stack Overflow](https://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map/9371137#9371137)\r\n"
"  * [unordered\\_map \\- C\\+\\+ Reference](http://www.cplusplus.com/reference/unordered_map/unordered_map/)\r\n"
"* UI for osc type selection\r\n"
"  * JUCE: Tutorial: The ComboBox class https://docs.juce.com/master/tutorial_combo_box.html\r\n"
"* Parameter (such as volume) change without glitches\r\n"
"  * [JUCE: LinearSmoothedValue< FloatType > Class Template Reference](https://docs.juce.com/master/classLinearSmoothedValue.html#a6cc025f0d2de6ac18dc15368a31e893c)\r\n"
"* Misc\r\n"
"  * [c\\+\\+ \\- Can't use modulus on doubles? \\- Stack Overflow](https://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles)\r\n"
"  * [visual studio \\- Default directory where new classes are stored? \\- Stack Overflow](https://stackoverflow.com/questions/9700170/default-directory-where-new-classes-are-stored)\r\n"
"* JUCE Sliders\r\n"
"  * [JUCE: Slider Class Reference](https://docs.juce.com/master/classSlider.html)\r\n"
"  * [JUCE: Tutorial: The Slider class](https://docs.juce.com/master/tutorial_slider_values.html)\r\n"
"  * [Integer Slider \\- General JUCE discussion \\- JUCE](https://forum.juce.com/t/integer-slider/26884)\r\n"
"* C++ Math\r\n"
"  * [pow \\- C\\+\\+ Reference](http://www.cplusplus.com/reference/cmath/pow/)\r\n"
"* JUCE Source Control Practices\r\n"
"  * [Having problems with source control \\- Audio Plugins \\- JUCE](https://forum.juce.com/t/having-problems-with-source-control/19225/3)\r\n"
"  * [JUCE project setup process \\| CredlandAudio](http://blog.credland.net/2016/05/juce-project-setup-process.html)\r\n"
"* General Source Control\r\n"
"  * [What\xca\xbcs a Fast Forward Merge?](https://sandofsky.com/images/fast_forward.pdf)\r\n"
"* Adding files to JUCE Project\r\n"
"  * This has to be done trough Projucer. For example, to add a new cpp class file, don't do it using Visual Studio UI. Open \"File Explorer\" in Projucer. Click on \"(+)\", then \"Add New CPP File...\" or if you already had used Visual Studio or some"
"thing else, \"Add Existing Files...\"\r\n"
"  * This way, new files will be part of the \"JUCE Project\" and any IDE export will have them.\r\n"
"  * See: [JUCE: Tutorial: Projucer Part 2: Manage your Projucer projects](https://docs.juce.com/master/tutorial_manage_projucer_project.html)\r\n"
"* Upgrading JUCE\r\n"
"  * I wan't to use the ADSR class that is mentioned in the documentation. Apparently, it was introduced in version 5.4.2, whereas I had version 5.4.1\r\n"
"  * To upgrade the JUCE library, open Projucer. I think it does an \"check upgrades\" at the beginning. It asks to download newer version. \r\n"
"  * (I first attempted to download it on the existing folder, however that failed.)\r\n"
"  * Download it to JUCE-5.4.2 folder\r\n"
"  * Open the Projucer in the newer version. Open existing project.\r\n"
"  * File > Global Paths\r\n"
"  * Set \"Path to JUCE\" and \"JUCE Modules\" to `C:\\Users\\veliu\\JUCE-5.4.2` paths. \r\n"
"  * Now when I click on module names in \"Modules\" section, I see that their version is 5.4.2.\r\n"
"  * Save the Projucer project, and open it in the IDE again \"Save an open in IDE\".\r\n"
"  * Looks like, module files are not copied to Visual Studio project but their path is known by VS.\r\n"
"  * Build project again, and I must good to go.\r\n"
"* ADSR\r\n"
"  * [JUCE: ADSR Class Reference](https://docs.juce.com/develop/classADSR.html)\r\n"
"  * [JUCE: ADSR::Parameters Struct Reference](https://docs.juce.com/develop/structADSR_1_1Parameters.html)\r\n"
"  * Meaning of ADSR stages [Envelope \\(music\\) \\- Wikipedia](https://en.wikipedia.org/wiki/Envelope_(music))\r\n"
"* C++ Structs\r\n"
"  * [4\\.7 \xe2\x80\x94 Structs \\| Learn C\\+\\+](https://www.learncpp.com/cpp-tutorial/47-structs/)\r\n"
"\r\n"
"\r\n";

const char* README_md = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 6683; return README_md;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README_md"
};

const char* originalFilenames[] =
{
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
