<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://www.unrealengine.com/">
    <img src="images/UE_Logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Unreal Engine Toolbox</h3>

  <p align="center">
    An awesome repository full of nice plugins to add to your next Unreal Engine 5 project! <br />
    Made By Samuel Potvin
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#Plugins">Plugins</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This git repository contains all the nice plugins that I developped during my time at the University and during my spare time. These plugins can be very nice to have in the context of a GameJam or a personnal project. All the plugins contained in this repository are built to be multiplayer ready for any multiplayer games you would want to create.

### Built With

- Unreal Engine 5
- C++ project

<!-- GETTING STARTED -->
## Getting Started

This is where you'll find everyting to know about how to install the plugins in your Unreal Engine project.

### Prerequisites

* Unreal engine 5.1 or later
* Visual Studio 2022 or Rider (Rider if you can)

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Samu3lPo/UnrealEngine_Toolbox.git
   ```
2. Extract files to the folder plugin of your Unreal5.1+ project
   Your project should look like this :
   ```sh
   YOUR_GAME/Plugins/[All the new plugin folders]/
   ```
3. Open your Unreal project and go to Settings > Plugins to enable all the plugins.
4. Close Unreal and make sure that your c++ project is build. If the build failed, follow next instructions:
   - Delete following folders : /Binaries, /Intermediate, /DerivedDataCache, /Plugins/[PluginName]/Binaries, /Plugins/[PluginName]/Intermediate
   - Regenerate project solution (right click on the .uproject file > generate Visual Studio code solution)
   - Open the new solution with your IDE
   - Build your project and run it with your IDE.
5. You should now have new plugins folder in your Unreal project tree.

For more details about installing Visual Studio for Unreal Engine, please refor to the [Documentation](https://docs.unrealengine.com/5.1/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/)

For more details about installing Rider for Unreal Engine, please refor to the [Documentation](https://www.jetbrains.com/help/rider/Unreal_Engine__Before_You_Start.html)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Plugins

### - Unreal Online Toolbox plugin [(Source Code)](https://github.com/Samu3lPo/UnrealEngine_Toolbox/tree/master/UnrealOnlineToolbox/Source/OnlineToolbox)

To take full advantage of this Plugin's features, you'll need to configure your project to use an online subsystem such as Steam or Epic Online Services (EOS).

Here is a [course page](https://dev.epicgames.com/community/learning/courses/1px/unreal-engine-the-eos-online-subsystem-oss-plugin/Lnjn/unreal-engine-introduction) that explains how to setup EOS in your game. This is the one I recommend since it's the one I used to test this plugin and it is free.

- [Documentation for Steam](https://docs.unrealengine.com/5.1/en-US/online-subsystem-steam-interface-in-unreal-engine/)
- [Documentation for Epic Game](https://docs.unrealengine.com/5.1/en-US/online-subsystem-eos-plugin-in-unreal-engine/)

<ins>SESSION SUBSYSTEM</ins>

The session subsystem allow you to connect many players to a session or even to chose which session a player want to join. This system work out of the box with the null subsystem from Unreal but you can use any online subsystem if you add the correct configuration to your project.

<ins>IDENTITY SUBSYSTEM</ins>

The identity subsystem allow you to connect to your account from any online subsystem. This system gives you all the basic functionnalities to login and logout to your account in game.

<ins>ACHIEVEMENTS SUBSYSTEM</ins>

The achivements subsystem allow you to creates achievements in your game through any online subsystem. This system gives you all the basic functionnalities to handle achievements from any online services that you created for your game.

### - Ability System plugin [(Source Code)](https://github.com/Samu3lPo/UnrealEngine_Toolbox/tree/master/AbilitySystem/Source/AbilitySystem)

This plugin is a simplified and inspired version of the Gameplay Ability System (GAS). It takes advantage of the [Gameplay Tags](https://docs.unrealengine.com/5.1/en-US/using-gameplay-tags-in-unreal-engine/) in Unreal to further enhance the implementation of skills in your next game. This plugin gives you the potential to creates and handle abilities and modifiers in your game. Games such as MMORPGs, where the gameplay is skill-based, would benefit greatly from this system. This system is made to be multiplayer ready.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Samuel Potvin - [Linkedin](https://linkedin.com/in/samuel-potvin-699b5a23a) - samuel.potvin25@gmail.com

My Personnal Project Link: [https://github.com/Samu3lPo/GameDevPlayground](https://github.com/Samu3lPo/GameDevPlayground)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Samu3lPo/UnrealEngine_Toolbox/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/samuel-potvin-699b5a23a
