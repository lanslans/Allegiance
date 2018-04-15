cscript /e:jscript /NoLogo XMLXForm.js AGCEvents.xml AGCEventsCPP.xsl %1AGCEventsCPP.h
cscript /e:jscript /NoLogo XMLXForm.js AGCEvents.xml AGCEventsRC2.xsl %1AGCEventsRC2.rc2
cscript /e:jscript /NoLogo XMLXForm.js AGCEvents.xml AGCEventsRCH.xsl %1AGCEventsRCH.h
cscript /e:jscript /NoLogo XMLXForm.js AGCEvents.xml AGCEventsMC.xsl %1AGCEventsMC.mc
mc.exe -r %1 -h %1 %1AGCEventsMC.mc
