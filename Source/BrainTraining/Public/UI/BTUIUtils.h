#pragma once

#include "Blueprint/UserWidget.h"

class BTUIUtils
{
public:
	template<typename T>
	static T* GetInitializedWidget(UWorld* WorldContextObject, TSubclassOf<UUserWidget> WidgetClass)
	{
		if(!WidgetClass) return nullptr;

		const auto Widget = CreateWidget<T>(WorldContextObject, WidgetClass);
		check(Widget);

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Collapsed);
		return Widget;
	}
};
