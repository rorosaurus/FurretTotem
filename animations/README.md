# Finalized animations

The original pixel art animation was done by the extremely talented [Alex Illustration](https://www.artstation.com/alexillustration)! My wife and I modified the basic animation in Photoshop to make all the other animations!

The animations with transparent (dynamically generated) backgrounds aren't *perfectly* re-created here, but you get the idea!

Here they are, sorted by when they were added to the animation pool!

## v0.1
![basic-walk](finalized/basic-walk.gif)
![transparent-walk](finalized/transparent-walk.gif)

## ABGT Weekender 2019
![abgtw](finalized/abgtw.gif)
![furret-friends](finalized/furret-friends.gif)
![head-bob](finalized/head-bob.gif)
![mantykebubbles](finalized/mantykebubbles.gif)
![rave-furret](finalized/rave-furret.gif)

## Shambhala 2019
![3rd-eye-blink](finalized/3rd-eye-blink.gif)
![crop-1](finalized/crop-1.gif)
![crop-2-truncated](finalized/crop-2-truncated.gif)
![crop-3-truncated](finalized/crop-3-truncated.gif)
![crop-4](finalized/crop-4.gif)
![heart-eyes](finalized/heart-eyes.gif)
![test-shambhala-6](finalized/test-shambhala-6.gif)
![test-shambhala-9](finalized/test-shambhala-9.gif)
![upside-down-walk](finalized/upside-down-walk.gif)
![walkoff-vertical-solo](finalized/walkoff-vertical-solo.gif)
![walkoff-vertical-truncated](finalized/walkoff-vertical-truncated.gif)
![walkoff-walkon-upsidedown](finalized/walkoff-walkon-upsidedown.gif)
![walkoff-walkon](finalized/walkoff-walkon.gif)

## Burning Man 2019
Ran out of time! 😅

## Alchemy Tour 2019
![gitchfurret-CHONK](finalized/gitchfurret-CHONK.gif)
![gitchfurret-fractally](finalized/gitchfurret-fractally.gif)
![gitchfurret-horror](finalized/gitchfurret-horror.gif)
![gitchfurret-minor](finalized/gitchfurret-minor.gif)
![gitchfurret-oface](finalized/gitchfurret-oface.gif)
![gitchfurret-printing](finalized/gitchfurret-printing.gif)
![gitchfurret-wavy](finalized/gitchfurret-wavy.gif)
![gitchfurret2](finalized/gitchfurret2.gif)
![outrun](finalized/outrun.gif)

## Dreamstate SoCal 2019
![outrun-glasses](finalized/outrun-glasses.gif)
![nyanfurret](finalized/nyanfurret.gif)
![bmo](finalized/bmo.gif)
![galactic-furret-paralax](finalized/galactic-furret-paralax.gif)

# Limitations
* SPIFFS filenames can't be too long, or files will not upload. (Move to FatFS!)
* Little color variety: due to memory constraints on ESP32 with 128x64px, use < 32 colors
* Short looped animations: due to memory constraints on ESP32 with 128x64px, use < 20 frames total (or is it < 20kB filesize?)

# Future design philosophy
* Allow every animation to have 3 phases: 1 and 3 are optional and play once.  2 loops as long as needed.
  1. intro
  2. loop
  3. outro
  
* transparent backgrounds (alpha layer) are allowed so we can change/generate the backgrounds

# Future Animation ideas

* Furret eats a berry and then his eyes change (ditto or dilated pupils?) and he grows a smile
* the worm?
* ditto furret face
* additional crops for furret walking video
* add a microphone and do beat analysis.  adjust frame delay until furret walking lines up with the beat.
