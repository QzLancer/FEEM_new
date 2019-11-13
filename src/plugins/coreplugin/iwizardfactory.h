#pragma once

#include <coreplugin/core_global.h>
#include <coreplugin/id.h>
//#include <coreplugin/featureprovider.h>

#include <QObject>
#include <QIcon>
#include <QObject>
#include <QString>

#include <QSet>

#include <functional>

QT_FORWARD_DECLARE_CLASS(QAction)

namespace Utils { class Wizard; }

namespace Core {

class CorePlugin; 

class FEEM_CORE_EXPORT IWizardFactory : public QObject
{
    Q_OBJECT
public:
    enum WizardKind {
        FileWizard = 0x01,
        ProjectWizard = 0x02
    };
    enum WizardFlag {
        PlatformIndependent = 0x01,
        ForceCapitalLetterForFileName = 0x02
    };
    Q_DECLARE_FLAGS(WizardFlags, WizardFlag)

    Id id() const { return m_id; }
    WizardKind kind() const { return /*m_supportedProjectTypes.isEmpty() ? FileWizard : */ProjectWizard; }
    QIcon icon() const { return m_icon; }
    QString iconText() const { return m_iconText; }
    QString description() const { return m_description; }
    QString displayName() const { return m_displayName; }
    QString category() const { return m_category; }
    QString displayCategory() const { return m_displayCategory; }
    QString descriptionImage() const { return m_descriptionImage; }
//    QSet<Id> requiredFeatures() const { return m_requiredFeatures; }
    WizardFlags flags() const { return m_flags; }
//    QSet<Id> supportedProjectTypes() const { return m_supportedProjectTypes; }

    void setId(const Id id) { m_id = id; }
//    void setSupportedProjectTypes(const QSet<Id> &projectTypes) { m_supportedProjectTypes = projectTypes; }
    void setIcon(const QIcon &icon) { m_icon = icon; }
    void setIconText(const QString &iconText) { m_iconText = iconText; }
    void setDescription(const QString &description) { m_description = description; }
    void setDisplayName(const QString &displayName) { m_displayName = displayName; }
    void setCategory(const QString &category) { m_category = category; }
    void setDisplayCategory(const QString &displayCategory) { m_displayCategory = displayCategory; }
    void setDescriptionImage(const QString &descriptionImage) { m_descriptionImage = descriptionImage; }
//    void setRequiredFeatures(const QSet<Id> &featureSet) { m_requiredFeatures = featureSet; }
//    void addRequiredFeature(const Id &feature) { m_requiredFeatures |= feature; }
    void setFlags(WizardFlags flags) { m_flags = flags; }

    QString runPath(const QString &defaultPath);

    // Does bookkeeping and the calls runWizardImpl. Please implement that.
    Utils::Wizard *runWizard(const QString &path, QWidget *parent, /*Id platform,*/
                             const QVariantMap &variables);

//    virtual bool isAvailable(Id platformId) const;
//    QSet<Id> supportedPlatforms() const;

    using FactoryCreator = std::function<QList<IWizardFactory *>()>;
    static void registerFactoryCreator(const FactoryCreator &creator);

    // Utility to find all registered wizards
    static QList<IWizardFactory*> allWizardFactories();
//    static QSet<Id> allAvailablePlatforms();
//    static QString displayNameForPlatform(Id i);

//    static void registerFeatureProvider(IFeatureProvider *provider);

    static bool isWizardRunning();
    static QWidget *currentWizard();

    static void requestNewItemDialog(const QString &title,
                                     const QList<IWizardFactory *> &factories,
                                     const QString &defaultLocation,
                                     const QVariantMap &extraVariables);

protected:
//    QSet<Id> pluginFeatures() const;
//    QSet<Id> availableFeatures(Id platformId) const;

    virtual Utils::Wizard *runWizardImpl(const QString &path, QWidget *parent, /*Id platform,*/
                                         const QVariantMap &variables) = 0;

private:
    static void initialize();
//    static void destroyFeatureProvider();

    static void clearWizardFactories();

    QAction *m_action = nullptr;
    QIcon m_icon;
    QString m_iconText;
    QString m_description;
    QString m_displayName;
    QString m_category;
    QString m_displayCategory;
    QString m_descriptionImage;
//    QSet<Id> m_requiredFeatures;
    QSet<Id> m_supportedProjectTypes;
    WizardFlags m_flags;
    Id m_id;

    friend class CorePlugin;
};

} // namespace Core

Q_DECLARE_OPERATORS_FOR_FLAGS(Core::IWizardFactory::WizardFlags)
