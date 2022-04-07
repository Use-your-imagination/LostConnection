// Copyright (c) 2022 Arkadiy Zakharov

#include "Constants.h"

#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"

FString Constants::styles = TEXT(R"(html {
    font-family: Calibri;
}

td {
    width: 20%;
}

.patch-notes {
    background-image: url([0]);
    background-size: 100%;
}

.version {
    margin-bottom: 4%;
    text-align: center;
}

.patch-notes-container {
    margin-top: 0.5%;
    margin-bottom: 0.5%;
    margin-left: 30%;
    margin-right: 30%;
    align-items: center;
    background-color: rgba([1]);
    border-radius: 5px;
}

.category {
    margin-left: 10px;
    margin-bottom: 10px;
    font-size: xx-large;
}

.element {
    font-size: x-large;
    margin-bottom: 7px;
    margin-left: 20px;
}

.note {
    margin-left: 20px;
    font-size: large;
    color: rgba(0, 0, 0, 0.7);
}

.project-logo {
    width: 64px;
    height: 64px;
    margin-top: 18px;
    margin-left: 40px;
    float: left;
}

.title {
    color: white;
    margin-left: 20%;
    font-style: italic;
    padding-top: 30.5px;
    float: left;
}

.title-container {
    margin-top: 1%;
    background-color: rgb(16, 28, 36);
    font-size: xx-large;
    margin-left: 20%;
    margin-right: 20%;
    height: 100px;
}

.link-to-patch {
    background-color: black;
    color: white;
    text-decoration: none;
    display: inline-block;
    cursor: pointer;
    border: 1px solid transparent;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    width: 100%;
    user-select: none;
    text-align: center;
    padding-top: 20%;
    padding-bottom: 20%;
}

.links-container {
    margin-top: 5%;
    margin-left: 25%;
    margin-right: 25%;
}
)");

FString Constants::defaultFavicon = TEXT("");

FString Constants::defaultBackgroundImage = TEXT("");

const FString Constants::stylesFileName = TEXT("styles.css");

void Constants::initBackgroundColors(const TArray<float>& rgbaColor)
{
    Constants::styles = Constants::styles.Replace(TEXT("[1]"), *FString::Printf(TEXT("%f, %f, %f, %f"), rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]));
}

void Constants::initBackgroundImage(const FString& backgroundImage)
{
    Constants::styles = Constants::styles.Replace(TEXT("[0]"), *backgroundImage);
}

void Constants::initDefaults()
{
    FString resourceFolder = IPluginManager::Get().FindPlugin(TEXT("PatchNotes"))->GetBaseDir() / TEXT("Resources");

    FFileHelper::LoadFileToString(Constants::defaultFavicon, *(resourceFolder / TEXT("default_favicon.b64")));

    FFileHelper::LoadFileToString(Constants::defaultBackgroundImage, *(resourceFolder / TEXT("default_background_image.b64")));

    Constants::defaultFavicon.InsertAt(0, TEXT("data:image/x-icon;base64,"));

    Constants::defaultBackgroundImage.InsertAt(0, TEXT("data:image/x-png;base64,"));
}

const FString& Constants::getStyles()
{
	return styles;
}

const FString& Constants::getDefaultFavicon()
{
    return defaultFavicon;
}

const FString& Constants::getDefaultBackgroundImage()
{
    return defaultBackgroundImage;
}
