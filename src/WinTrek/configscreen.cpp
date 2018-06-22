#include "pch.h"
#include "valuetransform.h"

#include "ui.h"

class ConfigScreen :
    public Screen
{
private:
    TRef<UiEngine>           m_pUiEngine;
    TRef<GameConfigurationWrapper> m_pConfiguration;
    TRef<Image>         m_pimage;
    TRef<TrekApp> m_pTrekApp;
    std::unique_ptr<ConfigScreenHooks> m_phooks;

    TRef<SimpleModifiableValue<bool>> m_pHasChanges;

public:
    Image* GetImage()
    {
        return m_pimage;
    }

    ConfigScreen(TrekApp* pTrekApp, UiEngine* pUiEngine, UpdatingConfiguration* pconfiguration, std::unique_ptr<ConfigScreenHooks> phooks) :
        m_pTrekApp(pTrekApp),
        m_pUiEngine(pUiEngine),
        m_phooks(std::move(phooks))
    {
        m_pConfiguration = new GameConfigurationWrapper(new UpdatingConfiguration(std::make_shared<UpdatingConfigurationStoreTransformer>(pconfiguration)));
        m_pHasChanges = new SimpleModifiableValue<bool>(false);

        std::map<std::string, std::shared_ptr<Exposer>> map;
        map["Has changes"] = BooleanExposer::Create(m_pHasChanges);
        map["Commit changes"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink([this]() {
            m_pConfiguration->Update();
            return true;
        }));
        map["Close sink"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->CloseConfiguration));
        map["Quit mission sink"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->ExitMission));
        map["Quit allegiance sink"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->ExitAllegiance));
        map["Is in mission"] = TypeExposer<TRef<Boolean>>::Create(m_phooks->pIsInMission);
        map["Open keymap popup"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->OpenKeymapPopup));
        map["Open ping popup"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->OpenPingPopup));
        map["Open mission info popup"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->OpenMissionInfoPopup));
        map["Open help popup"] = TypeExposer<TRef<IEventSink>>::Create(new CallbackSink(m_phooks->OpenHelpPopup));
        map["time"] = NumberExposer::Create(GetEngineWindow()->GetTime());

        //graphics
        map["Configuration.Graphics.Fullscreen"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetGraphicsFullscreen());
        map["Configuration.Graphics.ResolutionX"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetGraphicsResolutionX());
        map["Configuration.Graphics.ResolutionY"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetGraphicsResolutionY());
        map["Configuration.Graphics.UseVSync"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetGraphicsUseVSync());
        map["Configuration.Graphics.UseAntiAliasing"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetGraphicsUseAntiAliasing());

        map["Configuration.Graphics.MaxTextureSizeLevel"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetGraphicsMaxTextureSizeLevel());

        //online
        map["Configuration.Online.CharacterName"] = TypeExposer<TRef<SimpleModifiableValue<ZString>>>::Create(m_pConfiguration->GetOnlineCharacterName());
        map["Configuration.Online.SquadTag"] = TypeExposer<TRef<SimpleModifiableValue<ZString>>>::Create(m_pConfiguration->GetOnlineSquadTag());
        map["Configuration.Online.OfficerToken"] = TypeExposer<TRef<SimpleModifiableValue<ZString>>>::Create(m_pConfiguration->GetOnlineOfficerToken());

        map["AvailableSquadTags"] = TypeExposer<sol::as_table_t<std::vector<std::string>>>::Create(GetAvailableSquadTags());
        map["AvailableTokens"] = TypeExposer<TRef<UiList<TRef<StringValue>>>>::Create(GetAvailableTokens());

        //debug
        map["Configuration.Debug.LogToFile"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetDebugLogToFile());
        map["Configuration.Debug.LogToOutput"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetDebugLogToOutput());
        map["Configuration.Debug.Lua"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetDebugLua());
        map["Configuration.Debug.Mdl"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetDebugMdl());
        map["Configuration.Debug.Window"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetDebugWindow());

        //ui
        map["Configuration.Ui.ShowStartupCreditsMovie"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetUiShowStartupCreditsMovie());
        map["Configuration.Ui.ShowStartupIntroMovie"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetUiShowStartupIntroMovie());
        map["Configuration.Ui.ShowStartupTrainingSuggestion"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetUiShowStartupTrainingSuggestion());
        map["Configuration.Ui.UseOldUi"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetUiUseOldUi());

        //sound
        map["Configuration.Sound.EffectVolume"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetSoundEffectVolume());
        map["Configuration.Sound.VoiceVolume"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetSoundVoiceVolume());

        //joystick
        map["Configuration.Joystick.ControlsLinear"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetJoystickControlsLinear());
        map["Configuration.Joystick.Deadzone"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetJoystickDeadzoneSize());
        map["Configuration.Joystick.FlipYAxis"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetJoystickFlipYAxis());
        map["Configuration.Joystick.UseMouseAsJoystick"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetJoystickUseMouseAsJoystick());
        map["Configuration.Joystick.ShowDirectionIndicator"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetJoystickShowDirectionIndicator());
        map["Configuration.Joystick.EnableForceFeedback"] = TypeExposer<TRef<SimpleModifiableValue<bool>>>::Create(m_pConfiguration->GetJoystickEnableForceFeedback());

        //mouse
        map["Configuration.Mouse.Sensitivity"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetMouseSensitivity());
        map["Configuration.Mouse.Acceleration"] = TypeExposer<TRef<SimpleModifiableValue<float>>>::Create(m_pConfiguration->GetMouseAcceleration());

        m_pimage = pUiEngine->LoadImageFromLua(UiScreenConfiguration::Create("menuconfig/configscreen.lua", map));
    }

    std::vector<std::string> GetAvailableSquadTags() {
        std::vector<std::string> result = std::vector<std::string>({
            ""
        });

        for (std::shared_ptr<CallsignSquad> squad : m_pTrekApp->GetCallsignHandler()->GetAvailableSquads()) {
            result.push_back(std::string(squad->GetCleanedTag()));
        }

        return result;
    }

    TRef<UiList<TRef<StringValue>>> GetAvailableTokens() {
        return new TransformedList<TRef<StringValue>, ZString>([this](ZString tag) {
            std::shared_ptr<CallsignSquad> squad = m_pTrekApp->GetCallsignHandler()->GetSquadForTag(tag);

            std::vector<TRef<StringValue>> result = std::vector<TRef<StringValue>>({
                new StringValue("")
            });
            if (squad != nullptr) {
                for (ZString str : squad->GetAvailableOfficerTokens()) {
                    result.push_back(new StringValue(str));
                }
            }
            return result;
        }, (TRef<StringValue>)m_pConfiguration->GetOnlineSquadTag());
    }

    ~ConfigScreen() {
        m_pConfiguration->Update();
    }

    void OnFrame() override {
        if (m_pHasChanges->GetValue() != m_pConfiguration->HasChanged()) {
            m_pHasChanges->SetValue(m_pConfiguration->HasChanged());
        }
    }

    Pane* GetPane()
    {
        return nullptr;
    }
};

TRef<Screen> CreateConfigScreen(TrekApp* pTrekApp, UiEngine* pUiEngine, UpdatingConfiguration* pconfiguration, std::unique_ptr<ConfigScreenHooks> phooks)
{
    return new ConfigScreen(pTrekApp, pUiEngine, pconfiguration, std::move(phooks));
}


