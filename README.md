# Scoreboard WLB Esslingen

Scoreboard application for Württembergische Landesbühne Esslingen. OpenFrameworks project (originally Windows/Visual Studio, macOS support in progress).

**Branches:** `master` = original code archive · `reconstruction` = macOS build work

## Requirements

- **openFrameworks 0.9.8** for macOS: [of_v0.9.8_osx_release](https://openframeworks.cc/versions/v0.9.8/of_v0.9.8_osx_release.zip)
- Addons (included in OF 0.9.8): ofxGui, ofxParamEdit, ofxPointilize, ofxSegmentDisplay

## Setup (macOS)

1. Download and extract OF 0.9.8 for macOS.
2. Place the extracted folder (`of_v0.9.8_osx_release`) next to this repo and rename to `openFrameworks`, or create a symlink:
   ```bash
   cd .. && ln -s of_v0.9.8_osx_release openFrameworks
   ```
3. Build:
   - **Make:** `make` (from project root)
   - **Xcode:** Use projectGenerator to create an Xcode project, or open an existing `.xcodeproj` if present.

## Original (Windows)

Built with Visual Studio 2015, OF 0.9.8 vs release. See `Scoreboard.vcxproj` for reference.
