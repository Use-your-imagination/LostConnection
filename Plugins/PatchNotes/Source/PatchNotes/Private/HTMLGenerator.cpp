// Copyright (c) 2022 Arkadiy Zakharov

#include "HTMLGenerator.h"

#include "Misc/FileHelper.h"

#include "Utility.h"
#include "Constants.h"

void HTMLGenerator::addPageInformation(const FString& projectName, const FString& version, const TSharedPtr<FJsonObject>& settings)
{
	TSharedPtr<FJsonValue> logo = settings->TryGetField(TEXT("pathToProjectLogo"));

	html += FString::Printf(TEXT(R"(<!DOCTYPE html>

<html>

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>%s %s</title>
	<link href="styles.css" rel="stylesheet" type="text/css">
	<link rel="shortcut icon" href="%s" type="image/x-icon">
</head>

<body class="patch-notes">

)"), *projectName, *version, logo.IsValid() && !logo->IsNull() ? *logo->AsString() : *Constants::getDefaultFavicon());
}

void HTMLGenerator::addProjectNameAndVersion(const FString& projectName, const FString& version, const TSharedPtr<FJsonObject>& settings)
{
	this->addPageInformation(projectName, version, settings);

	html += FString::Printf(TEXT(R"(%s<h1 class="version">%s %s</h1>%s)"), TEXT("\t"), *projectName, *version, *HTMLGenerator::getLineTerminators(2));
}

void HTMLGenerator::addCategory(const FString& category)
{
	html += FString::Printf(TEXT(R"(%s<div class="patch-notes-container">%s)"), TEXT("\t"), *HTMLGenerator::getLineTerminators(1));

	html += FString::Printf(TEXT(R"(%s<div class="category">%s</div>%s)"), TEXT("\t\t"), *category, *HTMLGenerator::getLineTerminators(2));
}

void HTMLGenerator::addItem(const FString& item, const TArray<FString>& notes)
{
	html += FString::Printf(TEXT(R"(%s<div class="element">%s</div>%s)"), TEXT("\t\t"), *item, *HTMLGenerator::getLineTerminators(2));

	for (const FString& note : notes)
	{
		html += FString::Printf(TEXT(R"(%s<div class="note">&#8226; %s</div>%s)"), TEXT("\t\t"), *note, *HTMLGenerator::getLineTerminators(2));
	}
}

void HTMLGenerator::addCategoryEnd()
{
	html.RemoveAt(html.Len() - 1);

	html += TEXT("\t</div>") + HTMLGenerator::getLineTerminators(1);
}

void HTMLGenerator::addFooterInformation(const FString& information)
{
	html += FString::Printf(TEXT(R"(%s
</body>

</html>
)"), *information);
}

const FString& HTMLGenerator::getHTML() const
{
	return html;
}

FString HTMLGenerator::generatePatchLink(const FString& configurationName)
{
	return FString::Printf(TEXT(R"(%s<td><a href="%s.html" class="link-to-patch">%s</a></td>%s)"), TEXT("\t\t\t\t"), *configurationName, *configurationName, *HTMLGenerator::getLineTerminators(1));
}

FString HTMLGenerator::generateEmptyPatchLink()
{
	return TEXT("\t\t\t\t<td></td>") + HTMLGenerator::getLineTerminators(1);
}

FString HTMLGenerator::getLineTerminators(int32 count)
{
	FString result;

	for (int32 i = 0; i < count; i++)
	{
		result += TEXT("\n");
	}

	return result;
}

FString HTMLGenerator::makeTableRows(const TArray<FString>& data, int32 index, int32 columns)
{
	if (index >= data.Num())
	{
		return TEXT("");
	}

	FString tem = TEXT("\t\t\t<tr>") + HTMLGenerator::getLineTerminators(1);
	int32 current = 0;

	while (current != columns)
	{
		if (data.Num() == index + current)
		{
			break;
		}

		tem += data[index + current++];
	}

	tem += TEXT("\t\t\t</tr>") + HTMLGenerator::getLineTerminators(1);

	return tem + makeTableRows(data, index + current, columns);
}

void HTMLGenerator::generatePatchNotesHTML(const FString& fullOutPath, const FString& pathToConfigurationFile, const FString& pathToSettingsFile, TSharedPtr<SProgressBar>& progressBar)
{
	HTMLGenerator::generatePatchNotesHTML(fullOutPath, pathToConfigurationFile, Utility::getJSON(pathToSettingsFile), progressBar);
}

void HTMLGenerator::generatePatchNotesHTML(const FString& fullOutPath, const FString& pathToConfigurationFile, const TSharedPtr<FJsonObject>& settings, TSharedPtr<SProgressBar>& progressBar)
{
	HTMLGenerator generator;
	TSharedPtr<FJsonObject> configurationObject = Utility::getJSON(pathToConfigurationFile);
	const float startPercent = 5.0f;
	const float endPercent = 95.0f;
	const float percentsPerGeneratedValue = (endPercent - startPercent) / configurationObject->Values.Num() - 2; // exclude projectName and projectVersion
	int32 generatedValues = 1;

	generator.addProjectNameAndVersion(configurationObject->GetStringField("projectName"), configurationObject->GetStringField("projectVersion"), settings);

	for (const auto& categoryObject : configurationObject->Values)
	{
		const TSharedPtr<FJsonObject>* category = nullptr;

		if (!categoryObject.Value->TryGetObject(category) || (*category)->Values.Num() == 1)
		{
			continue;
		}

		generator.addCategory(categoryObject.Key);

		for (const auto& itemObject : category->Get()->Values)
		{
			const TSharedPtr<FJsonObject>* item = nullptr;

			if (!itemObject.Value->TryGetObject(item))
			{
				continue;
			}

			TArray<FString> notes;

			(*item)->TryGetStringArrayField(TEXT("notes"), notes);

			generator.addItem(itemObject.Key, notes);
		}

		generator.addCategoryEnd();

		Utility::runOnGameThread
		(
			[&progressBar, startPercent, generatedValues, percentsPerGeneratedValue]()
			{
				progressBar->SetPercent(startPercent + (StaticCast<float>(generatedValues) * percentsPerGeneratedValue));
			}
		);

		generatedValues++;
	}

	generator.addFooterInformation();

	FFileHelper::SaveStringToFile(generator.getHTML(), *fullOutPath, FFileHelper::EEncodingOptions::ForceUTF8);
}

void HTMLGenerator::generateIndexHTML(const FString& outPath, const FString& configurationName, const TSharedPtr<FJsonObject>& settings)
{
	TSharedPtr<FJsonValue> logo = settings->TryGetField(TEXT("pathToProjectLogo"));
	bool isCustomLogo = logo.IsValid() && !logo->IsNull();
	FString html = FString::Printf(TEXT(R"(<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>%s</title>
	<link href="styles.css" rel="stylesheet" type="text/css" />
	<link rel="shortcut icon" href="%s" type="image/x-icon">
</head>

<body>

	<div class="title-container">
		<img src="%s" alt="Project logo" class="project-logo" %s>
		<div class="title">Patch notes</div>
	</div>

	<div class="links-container">
		<table style="width: 100%%;">
		</table>
	</div>

</body>

</html>
)"),
*settings->GetStringField(TEXT("projectName")),
isCustomLogo ? *logo->AsString() : *Constants::getDefaultFavicon(),
isCustomLogo ? *logo->AsString() : TEXT(""),
isCustomLogo ? TEXT("") : TEXT("hidden"));

	FFileHelper::SaveStringToFile(html, *(outPath / TEXT("index.html")), FFileHelper::EEncodingOptions::ForceUTF8);

	HTMLGenerator::updateIndexHTML(outPath, configurationName);
}

void HTMLGenerator::updateIndexHTML(const FString& outPath, const FString& configurationName)
{
	static FString table = TEXT(R"(<table style="width: 100%;">)") + HTMLGenerator::getLineTerminators(1);
	TArray<FString> rows;
	TArray<FString> rowsData = { HTMLGenerator::generatePatchLink(configurationName) };
	FString indexHTMLData;

	FFileHelper::LoadFileToString(indexHTMLData, *(outPath / TEXT("index.html")));

	indexHTMLData.ParseIntoArray(rows, TEXT("\n"));

	indexHTMLData.Empty();

	for (FString& row : rows)
	{
		if (row.Find(configurationName) != INDEX_NONE)
		{
			return;
		}
		else if (row.Find(TEXT("<td></td>")) != INDEX_NONE || row.Find(TEXT("<tr>")) != INDEX_NONE || row.Find(TEXT("</tr>")) != INDEX_NONE)
		{
			continue;
		}
		else if (row.Find(TEXT("<td>")) != INDEX_NONE)
		{
			rowsData.Add(MoveTemp(row) + HTMLGenerator::getLineTerminators(1));

			continue;
		}

		indexHTMLData += MoveTemp(row) + HTMLGenerator::getLineTerminators(1);
	}
	 
	while (rowsData.Num() < 5)
	{
		rowsData.Add(HTMLGenerator::generateEmptyPatchLink());
	}

	indexHTMLData.InsertAt(indexHTMLData.Find(table) + table.Len(), HTMLGenerator::makeTableRows(rowsData, 0, 5));

	FFileHelper::SaveStringToFile(indexHTMLData, *(outPath / TEXT("index.html")), FFileHelper::EEncodingOptions::ForceUTF8);
}
