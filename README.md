<div id="top"></div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This app edits and reads ID3v2 tags from mp3 files. The app works from a cmd/terminal. More on ID3v2 tag [https://id3.org/d3v2.3.0](https://id3.org/d3v2.3.0)

**Now only APIC and text frames are supported**



<!-- GETTING STARTED -->
## Getting Started

Clone the repo with `git clone https://github.com/MariaMozgunova/ID3_tag_editor.git`



<!-- USAGE EXAMPLES -->
## Usage

Valid parameters for the program:
* `--filepath=<path>` - specify file to work with
* `--show` - shows all metadata in ID3v2 tag
* `--set=<name> --value=<value>` - sets frame with frame ID `name` equal to value `value`
* `--get=<name>` - shows frame with frame ID equl to `name`

Eample of usage: `mp3_meta_data_editor.exe --filepath=song.mp3 --set=TIT2 --value="Song name"`



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.



<!-- CONTACT -->
## Contact

Maria Mozgunova - [@mariamozgunova](https://t.me/mariamozgunova) - mariiamozgunova@gmail.com

Project Link: [https://github.com/MariaMozgunova/ID3_tag_editor](https://github.com/MariaMozgunova/ID3_tag_editor)

<p align="right">(<a href="#top">back to top</a>)</p>

