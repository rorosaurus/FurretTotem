# Finalized animations
Some of these have transparent backgrounds, which only show up as white here. Usually this transparency is filled with moving rainbow gradients on the real totem.

![3rd-eye-blink](finalized/3rd-eye-blink.gif)
![8bit-double](finalized/8bit-double.gif)
![8bit-transp-eyes](finalized/8bit-transp-eyes.gif)
![abgtw](finalized/abgtw.gif)
![basic-walk](finalized/basic-walk.gif)
![crop-1](finalized/crop-1.gif)
![crop-2-truncated](finalized/crop-2-truncated.gif)
![crop-3-truncated](finalized/crop-3-truncated.gif)
![crop-4](finalized/crop-4.gif)
![crop-5](finalized/crop-5.gif)
![ff-transparent](finalized/ff-transparent.gif)
![furret-friends](finalized/furret-friends.gif)
![gitchfurret-CHONK](finalized/gitchfurret-CHONK.gif)
![gitchfurret-fractally](finalized/gitchfurret-fractally.gif)
![gitchfurret-horror](finalized/gitchfurret-horror.gif)
![gitchfurret-minor](finalized/gitchfurret-minor.gif)
![gitchfurret-oface](finalized/gitchfurret-oface.gif)
![gitchfurret-printing](finalized/gitchfurret-printing.gif)
![gitchfurret-wavy](finalized/gitchfurret-wavy.gif)
![gitchfurret2](finalized/gitchfurret2.gif)
![head-bob](finalized/head-bob.gif)
![heart-eyes](finalized/heart-eyes.gif)
![kandi-walk](finalized/kandi-walk.gif)
![mantykebubbles](finalized/mantykebubbles.gif)
![nyancat](finalized/nyancat.gif)
![outrun](finalized/outrun.gif)
![rave-furret](finalized/rave-furret.gif)
![test-shambhala-5](finalized/test-shambhala-5.gif)
![test-shambhala-6](finalized/test-shambhala-6.gif)
![test-shambhala-7](finalized/test-shambhala-7.gif)
![test-shambhala-8](finalized/test-shambhala-8.gif)
![test-shambhala-9](finalized/test-shambhala-9.gif)
![test-shambhala](finalized/test-shambhala.gif)
![transparent-walk](finalized/transparent-walk.gif)
![upside-down-walk](finalized/upside-down-walk.gif)
![walkoff-vertical-solo](finalized/walkoff-vertical-solo.gif)
![walkoff-vertical-truncated](finalized/walkoff-vertical-truncated.gif)
![walkoff-walkon-right](finalized/walkoff-walkon-right.gif)
![walkoff-walkon-upsidedown](finalized/walkoff-walkon-upsidedown.gif)
![walkoff-walkon](finalized/walkoff-walkon.gif)

# Limitations
* SPIFFS filenames can't be too long, or files will not upload.
* Little color variety: due to memory constraints on ESP32 with 128x64px, use < 32 colors
* Short looped animations: due to memory constraints on ESP32 with 128x64px, use < 20 frames total (or is it < 20kB filesize?)

# Desired design
* Allow every animation to have 3 phases: 1 and 3 are optional and play once.  2 loops as long as needed.
  1. intro
  2. loop
  3. outro
  
* transparent backgrounds (alpha layer) are allowed so we can change/generate the backgrounds

# Animation ideas

* Furret eats a berry and then his eyes change (ditto or dilated pupils?) and he grows a smile
* the worm?
* ditto furret face
* additional crops for furret walking video
* add a microphone and do beat analysis.  adjust frame delay until furret walking lines up with the beat.