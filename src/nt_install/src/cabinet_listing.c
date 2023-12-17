/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

const char *_bi_cabinet_listing[] = {
    // sounds

    "blip.wa_", "*nt/sounds/blip.wav", "blip.wav",
    "chimes.wa_", "*nt/sounds/chimes.wav", "chimes.wav",
    "chord.wa_", "*nt/sounds/chord.wav", "chord.wav",
    "clickerx.wa_", "*nt/sounds/clickerx.wav", "clickerx.wav",
    "ding.wa_", "*nt/sounds/ding.wav", "ding.wav",
    "newalert.wa_", "*nt/sounds/newalert.wav", "newalert.wav",
    "newemail.wa_", "*nt/sounds/newemail.wav", "newemail.wav",
    "notify.wa_", "*nt/sounds/notify.wav", "notify.wav",
    "online.wa_", "*nt/sounds/online.wav", "online.wav",
    "recycle.wa_", "*nt/sounds/recycle.wav", "recycle.wav",
    "ringin.wa_", "*nt/sounds/ringin.wav", "ringin.wav",
    "ringout.wa_", "*nt/sounds/ringout.wav", "ringout.wav",
    "sndrec.wa_", "*nt/sounds/sndrec.wav", "sndrec.wav",
    // "sound104.wa_", "*nt/sounds/sound104.wav", "sound104.wav",
    // "sound105.wa_", "*nt/sounds/sound105.wav", "sound105.wav",
    // "sound108.wa_", "*nt/sounds/sound108.wav", "sound108.wav",
    // "sound111.wa_", "*nt/sounds/sound111.wav", "sound111.wav",
    // "sound112.wa_", "*nt/sounds/sound112.wav", "sound112.wav",
    // "sound12.wa_", "*nt/sounds/sound12.wav", "sound12.wav",
    // "sound131.wa_", "*nt/sounds/sound131.wav", "sound131.wav",
    // "sound136.wa_", "*nt/sounds/sound136.wav", "sound136.wav",
    // "sound13.wa_", "*nt/sounds/sound13.wav", "sound13.wav",
    // "sound14.wa_", "*nt/sounds/sound14.wav", "sound14.wav",
    // "sound16.wa_", "*nt/sounds/sound16.wav", "sound16.wav",
    // "sound17.wa_", "*nt/sounds/sound17.wav", "sound17.wav",
    // "sound181.wa_", "*nt/sounds/sound181.wav", "sound181.wav",
    // "sound18.wa_", "*nt/sounds/sound18.wav", "sound18.wav",
    // "sound19.wa_", "*nt/sounds/sound19.wav", "sound19.wav",
    // "sound1.wa_", "*nt/sounds/sound1.wav", "sound1.wav",
    // "sound20.wa_", "*nt/sounds/sound20.wav", "sound20.wav",
    // "sound21.wa_", "*nt/sounds/sound21.wav", "sound21.wav",
    // "sound22.wa_", "*nt/sounds/sound22.wav", "sound22.wav",
    // "sound240.wa_", "*nt/sounds/sound240.wav", "sound240.wav",
    // "sound243.wa_", "*nt/sounds/sound243.wav", "sound243.wav",
    // "sound24.wa_", "*nt/sounds/sound24.wav", "sound24.wav",
    // "sound25.wa_", "*nt/sounds/sound25.wav", "sound25.wav",
    // "sound26.wa_", "*nt/sounds/sound26.wav", "sound26.wav",
    // "sound27.wa_", "*nt/sounds/sound27.wav", "sound27.wav",
    // "sound28.wa_", "*nt/sounds/sound28.wav", "sound28.wav",
    // "sound29.wa_", "*nt/sounds/sound29.wav", "sound29.wav",
    // "sound30.wa_", "*nt/sounds/sound30.wav", "sound30.wav",
    // "sound34.wa_", "*nt/sounds/sound34.wav", "sound34.wav",
    // "sound35.wa_", "*nt/sounds/sound35.wav", "sound35.wav",
    // "sound36.wa_", "*nt/sounds/sound36.wav", "sound36.wav",
    // "sound38.wa_", "*nt/sounds/sound38.wav", "sound38.wav",
    // "sound39.wa_", "*nt/sounds/sound39.wav", "sound39.wav",
    // "sound3.wa_", "*nt/sounds/sound3.wav", "sound3.wav",
    // "sound42.wa_", "*nt/sounds/sound42.wav", "sound42.wav",
    // "sound43.wa_", "*nt/sounds/sound43.wav", "sound43.wav",
    // "sound45.wa_", "*nt/sounds/sound45.wav", "sound45.wav",
    // "sound49d.wa_", "*nt/sounds/sound49d.wav", "sound49d.wav",
    // "sound49.wa_", "*nt/sounds/sound49.wav", "sound49.wav",
    // "sound4.wa_", "*nt/sounds/sound4.wav", "sound4.wav",
    // "sound50.wa_", "*nt/sounds/sound50.wav", "sound50.wav",
    // "sound528.wa_", "*nt/sounds/sound528.wav", "sound528.wav",
    // "sound53.wa_", "*nt/sounds/sound53.wav", "sound53.wav",
    // "sound54.wa_", "*nt/sounds/sound54.wav", "sound54.wav",
    // "sound55.wa_", "*nt/sounds/sound55.wav", "sound55.wav",
    // "sound560.wa_", "*nt/sounds/sound560.wav", "sound560.wav",
    // "sound563.wa_", "*nt/sounds/sound563.wav", "sound563.wav",
    // "sound57.wa_", "*nt/sounds/sound57.wav", "sound57.wav",
    // "sound58.wa_", "*nt/sounds/sound58.wav", "sound58.wav",
    // "sound5.wa_", "*nt/sounds/sound5.wav", "sound5.wav",
    // "sound65.wa_", "*nt/sounds/sound65.wav", "sound65.wav",
    // "sound68.wa_", "*nt/sounds/sound68.wav", "sound68.wav",
    // "sound6.wa_", "*nt/sounds/sound6.wav", "sound6.wav",
    // "sound713.wa_", "*nt/sounds/sound713.wav", "sound713.wav",
    // "sound735.wa_", "*nt/sounds/sound735.wav", "sound735.wav",
    // "sound7.wa_", "*nt/sounds/sound7.wav", "sound7.wav",
    // "sound827.wa_", "*nt/sounds/sound827.wav", "sound827.wav",
    // "sound8.wa_", "*nt/sounds/sound8.wav", "sound8.wav",
    // "sound999.wa_", "*nt/sounds/sound999.wav", "sound999.wav",
    // "sound9.wa_", "*nt/sounds/sound9.wav", "sound9.wav",
    "start.wa_", "*nt/sounds/start.wav", "start.wav",
    "tada.wa_", "*nt/sounds/tada.wav", "tada.wav",
    "testsnd.wa_", "*nt/sounds/testsnd.wav", "testsnd.wav",
    "utopia~1.wa_", "*nt/sounds/utopia~1.wav", "utopia~1.wav",
    "utopia~2.wa_", "*nt/sounds/utopia~2.wav", "utopia~2.wav",
    "utopia~3.wa_", "*nt/sounds/utopia~3.wav", "utopia~3.wav",
    "utopia~4.wa_", "*nt/sounds/utopia~4.wav", "utopia~4.wav",
    "utopiaas.wa_", "*nt/sounds/utopiaas.wav", "utopiaas.wav",
    "utopiacl.wa_", "*nt/sounds/utopiacl.wav", "utopiacl.wav",
    "utopiacr.wa_", "*nt/sounds/utopiacr.wav", "utopiacr.wav",
    "utopiade.wa_", "*nt/sounds/utopiade.wav", "utopiade.wav",
    "utopiaer.wa_", "*nt/sounds/utopiaer.wav", "utopiaer.wav",
    "utopiaex.wa_", "*nt/sounds/utopiaex.wav", "utopiaex.wav",
    "utopiama.wa_", "*nt/sounds/utopiama.wav", "utopiama.wav",
    "utopiame.wa_", "*nt/sounds/utopiame.wav", "utopiame.wav",
    "utopiami.wa_", "*nt/sounds/utopiami.wav", "utopiami.wav",
    "utopiaop.wa_", "*nt/sounds/utopiaop.wav", "utopiaop.wav",
    "utopiaqu.wa_", "*nt/sounds/utopiaqu.wav", "utopiaqu.wav",
    "utopiare.wa_", "*nt/sounds/utopiare.wav", "utopiare.wav",
    "utopiawi.wa_", "*nt/sounds/utopiawi.wav", "utopiawi.wav",
    // "wmpaud1.wa_", "*nt/sounds/wmpaud1.wav", "wmpaud1.wav",
    // "wmpaud2.wa_", "*nt/sounds/wmpaud2.wav", "wmpaud2.wav",
    // "wmpaud3.wa_", "*nt/sounds/wmpaud3.wav", "wmpaud3.wav",
    // "wmpaud4.wa_", "*nt/sounds/wmpaud4.wav", "wmpaud4.wav",
    // "wmpaud5.wa_", "*nt/sounds/wmpaud5.wav", "wmpaud5.wav",
    // "wmpaud6.wa_", "*nt/sounds/wmpaud6.wav", "wmpaud6.wav",
    // "wmpaud7.wa_", "*nt/sounds/wmpaud7.wav", "wmpaud7.wav",
    // "wmpaud8.wa_", "*nt/sounds/wmpaud8.wav", "wmpaud8.wav",
    // "wmpaud9.wa_", "*nt/sounds/wmpaud9.wav", "wmpaud9.wav",
    "xpballn.wa_", "*nt/sounds/xpballn.wav", "xpballn.wav",
    "xpbatcrt.wa_", "*nt/sounds/xpbatcrt.wav", "xpbatcrt.wav",
    "xpbatlow.wa_", "*nt/sounds/xpbatlow.wav", "xpbatlow.wav",
    "xpblkpop.wa_", "*nt/sounds/xpblkpop.wav", "xpblkpop.wav",
    "xpcrtstp.wa_", "*nt/sounds/xpcrtstp.wav", "xpcrtstp.wav",
    "xpdef.wa_", "*nt/sounds/xpdef.wav", "xpdef.wav",
    "xpding.wa_", "*nt/sounds/xpding.wav", "xpding.wav",
    "xperror.wa_", "*nt/sounds/xperror.wav", "xperror.wav",
    "xpexcl.wa_", "*nt/sounds/xpexcl.wav", "xpexcl.wav",
    "xphdfail.wa_", "*nt/sounds/xphdfail.wav", "xphdfail.wav",
    "xphdinst.wa_", "*nt/sounds/xphdinst.wav", "xphdinst.wav",
    "xphdrem.wa_", "*nt/sounds/xphdrem.wav", "xphdrem.wav",
    "xpinfbar.wa_", "*nt/sounds/xpinfbar.wav", "xpinfbar.wav",
    "xplogoff.wa_", "*nt/sounds/xplogoff.wav", "xplogoff.wav",
    "xplogon.wa_", "*nt/sounds/xplogon.wav", "xplogon.wav",
    "xpmenu.wa_", "*nt/sounds/xpmenu.wav", "xpmenu.wav",
    "xpmin.wa_", "*nt/sounds/xpmin.wav", "xpmin.wav",
    "xpnotify.wa_", "*nt/sounds/xpnotify.wav", "xpnotify.wav",
    "xpprint.wa_", "*nt/sounds/xpprint.wav", "xpprint.wav",
    "xprecycl.wa_", "*nt/sounds/xprecycl.wav", "xprecycl.wav",
    "xprestor.wa_", "*nt/sounds/xprestor.wav", "xprestor.wav",
    "xpringin.wa_", "*nt/sounds/xpringin.wav", "xpringin.wav",
    "xprngout.wa_", "*nt/sounds/xprngout.wav", "xprngout.wav",
    "xpshutdn.wa_", "*nt/sounds/xpshutdn.wav", "xpshutdn.wav",
    "xpstartu.wa_", "*nt/sounds/xpstartu.wav", "xpstartu.wav",
    "xpstart.wa_", "*nt/sounds/xpstart.wav", "xpstart.wav",
    
    // user avatars

    "airplane.bm_", "*nt/images/user/avatars/airplane.bmp", "airplane.bmp",
    "astro.bm_", "*nt/images/user/avatars/astro.bmp", "astro.bmp",
    "beach.bm_", "*nt/images/user/avatars/beach.bmp", "beach.bmp",
    "butterfl.bm_", "*nt/images/user/avatars/butterfl.bmp", "butterfl.bmp",
    "car.bm_", "*nt/images/user/avatars/car.bmp", "car.bmp",
    "cat.bm_", "*nt/images/user/avatars/cat.bmp", "cat.bmp",
    "chess.bm_", "*nt/images/user/avatars/chess.bmp", "chess.bmp",
    "dirtbike.bm_", "*nt/images/user/avatars/dirtbike.bmp", "dirtbike.bmp",
    "dog.bm_", "*nt/images/user/avatars/dog.bmp", "dog.bmp",
    "drip.bm_", "*nt/images/user/avatars/drip.bmp", "drip.bmp",
    "duck.bm_", "*nt/images/user/avatars/duck.bmp", "duck.bmp",
    "fish.bm_", "*nt/images/user/avatars/fish.bmp", "fish.bmp",
    "frog.bm_", "*nt/images/user/avatars/frog.bmp", "frog.bmp",
    "guest.bm_", "*nt/images/user/avatars/guest.bmp", "guest.bmp",
    "guitar.bm_", "*nt/images/user/avatars/guitar.bmp", "guitar.bmp",
    "horses.bm_", "*nt/images/user/avatars/horses.bmp", "horses.bmp",
    "kick.bm_", "*nt/images/user/avatars/kick.bmp", "kick.bmp",
    "liftoff.bm_", "*nt/images/user/avatars/liftoff.bmp", "liftoff.bmp",
    "palmtree.bm_", "*nt/images/user/avatars/palmtree.bmp", "palmtree.bmp",
    "pnkflowr.bm_", "*nt/images/user/avatars/pnkflowr.bmp", "pnkflowr.bmp",
    "redflowr.bm_", "*nt/images/user/avatars/redflowr.bmp", "redflowr.bmp",
    "skater.bm_", "*nt/images/user/avatars/skater.bmp", "skater.bmp",
    "snwflake.bm_", "*nt/images/user/avatars/snwflake.bmp", "snwflake.bmp",
    "soccer.bm_", "*nt/images/user/avatars/soccer.bmp", "soccer.bmp",

    // wallpapers

    "bubbles.bm_", "*nt/images/user/wallpapers/bubbles.bmp", "bubbles.bmp",
    "coffeebn.bm_", "*nt/images/user/wallpapers/coffeebn.bmp", "coffeebn.bmp",
    "feather.bm_", "*nt/images/user/wallpapers/feather.bmp", "feather.bmp",
    "gonefish.bm_", "*nt/images/user/wallpapers/gonefish.bmp", "gonefish.bmp",
    "grnstone.bm_", "*nt/images/user/wallpapers/grnstone.bmp", "grnstone.bmp",
    "guest.bm_", "*nt/images/user/wallpapers/guest.bmp", "guest.bmp",
    "guitar.bm_", "*nt/images/user/wallpapers/guitar.bmp", "guitar.bmp",
    "horses.bm_", "*nt/images/user/wallpapers/horses.bmp", "horses.bmp",
    "prairie.bm_", "*nt/images/user/wallpapers/prairie.bmp", "prairie.bmp",
    "rhody.bm_", "*nt/images/user/wallpapers/rhody.bmp", "rhody.bmp",
    "rvrsumid.bm_", "*nt/images/user/wallpapers/rvrsumid.bmp", "rvrsumid.bmp",
    "santafe.bm_", "*nt/images/user/wallpapers/santafe.bmp", "santafe.bmp",
    "zapotec.bm_", "*nt/images/user/wallpapers/zapotec.bmp", "zapotec.bmp",
    "ascent.jp_", "*nt/images/user/wallpapers/ascent.jpg", "ascent.jpg",
    "autumn.jp_", "*nt/images/user/wallpapers/autumn.jpg", "autumn.jpg",
    "azul.jp_", "*nt/images/user/wallpapers/azul.jpg", "azul.jpg",
    "bliss.jp_", "*nt/images/user/wallpapers/bliss.jpg", "bliss.jpg",
    "bluehill.jp_", "*nt/images/user/wallpapers/bluehill.jpg", "bluehill.jpg",
    "clrdaybg.jp_", "*nt/images/user/wallpapers/clrdaybg.jpg", "clrdaybg.jpg",
    "crystal.jp_", "*nt/images/user/wallpapers/crystal.jpg", "crystal.jpg",
    "fiestabg.jp_", "*nt/images/user/wallpapers/fiestabg.jpg", "fiestabg.jpg",
    "follow.jp_", "*nt/images/user/wallpapers/follow.jpg", "follow.jpg",
    "friend.jp_", "*nt/images/user/wallpapers/friend.jpg", "friend.jpg",
    "home.jp_", "*nt/images/user/wallpapers/home.jpg", "home.jpg",
    "leavesbg.jp_", "*nt/images/user/wallpapers/leavesbg.jpg", "leavesbg.jpg",
    "maizebkg.jp_", "*nt/images/user/wallpapers/maizebkg.jpg", "maizebkg.jpg",
    "moon.jp_", "*nt/images/user/wallpapers/moon.jpg", "moon.jpg",
    "naturebg.jp_", "*nt/images/user/wallpapers/naturebg.jpg", "naturebg.jpg",
    "peace.jp_", "*nt/images/user/wallpapers/peace.jpg", "peace.jpg",
    "piechtbg.jp_", "*nt/images/user/wallpapers/piechtbg.jpg", "piechtbg.jpg",
    "power.jp_", "*nt/images/user/wallpapers/power.jpg", "power.jpg",
    "purplef.jp_", "*nt/images/user/wallpapers/purplef.jpg", "purplef.jpg",
    "radiance.jp_", "*nt/images/user/wallpapers/radiance.jpg", "radiance.jpg",
    "redmoon.jp_", "*nt/images/user/wallpapers/redmoon.jpg", "redmoon.jpg",
    "ripple.jp_", "*nt/images/user/wallpapers/ripple.jpg", "ripple.jpg",
    "stoneh.jp_", "*nt/images/user/wallpapers/stoneh.jpg", "stoneh.jpg",
    "sunfbkg.jp_", "*nt/images/user/wallpapers/sunfbkg.jpg", "sunfbkg.jpg",
    "sunset.jp_", "*nt/images/user/wallpapers/sunset.jpg", "sunset.jpg",
    "tulips.jp_", "*nt/images/user/wallpapers/tulips.jpg", "tulips.jpg",
    "vortec.jp_", "*nt/images/user/wallpapers/vortec.jpg", "vortec.jpg",
    "waterlil.jp_", "*nt/images/user/wallpapers/waterlil.jpg", "waterlil.jpg",
    "wind.jp_", "*nt/images/user/wallpapers/wind.jpg", "wind.jpg",
    "winter.jp_", "*nt/images/user/wallpapers/winter.jpg", "winter.jpg",
    "winxp.jp_", "*nt/images/user/wallpapers/winxp.jpg", "winxp.jpg",

    // advertisements

    "infospbz.bm_", "*nt/images/user/ad/infospbz.bmp", "infospbz.bmp",
    "infospce.bm_", "*nt/images/user/ad/infospce.bmp", "infospce.bmp",
    "music.bm_", "*nt/images/user/ad/music.bmp", "music.bmp",
    "swtchbrd.bm_", "*nt/images/user/ad/swtchbrd.bmp", "swtchbrd.bmp",
    "tunes.bm_", "*nt/images/user/ad/tunes.bmp", "tunes.bmp",
    "verisign.bm_", "*nt/images/user/ad/verisign.bmp", "verisign.bmp",
    "whowhere.bm_", "*nt/images/user/ad/whowhere.bmp", "whowhere.bmp",
    "yahoo.bm_", "*nt/images/user/ad/yahoo.bmp", "yahoo.bmp",

    // placeholders

    "bigfoot.bm_", "*nt/images/placeholders/bigfoot.bmp", "bigfoot.bmp",

    // ui

    "backdown.jp_", "*nt/images/user/ui/backdown.jpg", "backdown.jpg",
    "backoff.jp_", "*nt/images/user/ui/backoff.jpg", "backoff.jpg",
    "backover.jp_", "*nt/images/user/ui/backover.jpg", "backover.jpg",
    "backup.jp_", "*nt/images/user/ui/backup.jpg", "backup.jpg",
    "mslogo.jp_", "*nt/images/user/ui/mslogo.jpg", "mslogo.jpg",
    "newbtm1.jp_", "*nt/images/user/ui/newbtm1.jpg", "newbtm1.jpg",
    "newbtm8.jp_", "*nt/images/user/ui/newbtm8.jpg", "newbtm8.jpg",
    "newmark1.jp_", "*nt/images/user/ui/newmark1.jpg", "newmark1.jpg",
    "newmark8.jp_", "*nt/images/user/ui/newmark8.jpg", "newmark8.jpg",
    "newtop1.jp_", "*nt/images/user/ui/newtop1.jpg", "newtop1.jpg",
    "newtop8.jp_", "*nt/images/user/ui/newtop8.jpg", "newtop8.jpg",
    "nextdown.jp_", "*nt/images/user/ui/nextdown.jpg", "nextdown.jpg",
    "nextoff.jp_", "*nt/images/user/ui/nextoff.jpg", "nextoff.jpg",
    "nextover.jp_", "*nt/images/user/ui/nextover.jpg", "nextover.jpg",
    "nextup.jp_", "*nt/images/user/ui/nextup.jpg", "nextup.jpg",
    "oemcoa.jp_", "*nt/images/user/ui/oemcoa.jpg", "oemcoa.jpg",
    "skipdown.jp_", "*nt/images/user/ui/skipdown.jpg", "skipdown.jpg",
    "skipoff.jp_", "*nt/images/user/ui/skipoff.jpg", "skipoff.jpg",
    "skipover.jp_", "*nt/images/user/ui/skipover.jpg", "skipover.jpg",
    "skipup.jp_", "*nt/images/user/ui/skipup.jpg", "skipup.jpg",
    "wpaback.jp_", "*nt/images/user/ui/wpaback.jpg", "wpaback.jpg",
    "wpabtm.jp_", "*nt/images/user/ui/wpabtm.jpg", "wpabtm.jpg",
    "wpaflag.jp_", "*nt/images/user/ui/wpaflag.jpg", "wpaflag.jpg",
    "wpakey.jp_", "*nt/images/user/ui/wpakey.jpg", "wpakey.jpg",
    "wpatop.jp_", "*nt/images/user/ui/wpatop.jpg", "wpatop.jpg",
    "xptht02d.jp_", "*nt/images/user/ui/xptht02d.jpg", "xptht02d.jpg",
    "xptht02w.jp_", "*nt/images/user/ui/xptht02w.jpg", "xptht02w.jpg",
    "xptht03d.jp_", "*nt/images/user/ui/xptht03d.jpg", "xptht03d.jpg",
    "xptht03w.jp_", "*nt/images/user/ui/xptht03w.jpg", "xptht03w.jpg",
    "xptht04d.jp_", "*nt/images/user/ui/xptht04d.jpg", "xptht04d.jpg",
    "xptht04w.jp_", "*nt/images/user/ui/xptht04w.jpg", "xptht04w.jpg",
    "xptht05d.jp_", "*nt/images/user/ui/xptht05d.jpg", "xptht05d.jpg",
    "xptht06d.jp_", "*nt/images/user/ui/xptht06d.jpg", "xptht06d.jpg",
    "xptht06w.jp_", "*nt/images/user/ui/xptht06w.jpg", "xptht06w.jpg",
    "xptht07d.jp_", "*nt/images/user/ui/xptht07d.jpg", "xptht07d.jpg",
    "xptht07w.jp_", "*nt/images/user/ui/xptht07w.jpg", "xptht07w.jpg",
    "xptht08d.jp_", "*nt/images/user/ui/xptht08d.jpg", "xptht08d.jpg",
    "xptht08w.jp_", "*nt/images/user/ui/xptht08w.jpg", "xptht08w.jpg",
    "xptht09d.jp_", "*nt/images/user/ui/xptht09d.jpg", "xptht09d.jpg",
    "xptht10d.jp_", "*nt/images/user/ui/xptht10d.jpg", "xptht10d.jpg",
    "xptht10w.jp_", "*nt/images/user/ui/xptht10w.jpg", "xptht10w.jpg",
    "xptht11d.jp_", "*nt/images/user/ui/xptht11d.jpg", "xptht11d.jpg",
    "xptht11w.jp_", "*nt/images/user/ui/xptht11w.jpg", "xptht11w.jpg",
    "xptht12d.jp_", "*nt/images/user/ui/xptht12d.jpg", "xptht12d.jpg",
    "xptht12w.jp_", "*nt/images/user/ui/xptht12w.jpg", "xptht12w.jpg",
    "xptht13d.jp_", "*nt/images/user/ui/xptht13d.jpg", "xptht13d.jpg",
    "xptht14d.jp_", "*nt/images/user/ui/xptht14d.jpg", "xptht14d.jpg",
    "xptht15d.jp_", "*nt/images/user/ui/xptht15d.jpg", "xptht15d.jpg",
    "xptht16d.jp_", "*nt/images/user/ui/xptht16d.jpg", "xptht16d.jpg",
    "xptht17d.jp_", "*nt/images/user/ui/xptht17d.jpg", "xptht17d.jpg",
    "xptht18d.jp_", "*nt/images/user/ui/xptht18d.jpg", "xptht18d.jpg",
    "xptht19d.jp_", "*nt/images/user/ui/xptht19d.jpg", "xptht19d.jpg",
    "xptht20d.jp_", "*nt/images/user/ui/xptht20d.jpg", "xptht20d.jpg",

    // binaries
    "explorer.ex_", "*nt/binary/explorer.exe", "explorer.exe"
};