// 


#include "UI/CCWidgetComponent.h"

#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "Characters/CCBaseCharacter.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "UI/CCAttributeWidget.h"

void UCCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemData();
	
	// should do this: maybe beginplay of actor and component is not done one by one,
	// network latency
	if (!IsASCInitialized())
	{
		CrashCharacter->DEL_OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
}

void UCCWidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<ACCBaseCharacter>(GetOwner());
	AbilitySystemComponent = Cast<UCCAbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
	AttributeSet = Cast<UCCAttributeSet>(CrashCharacter->GetAttributeSet());
}

bool UCCWidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCCWidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributeInitialized)
	{
		AttributeSet->DEL_AttributeInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanged);
	}
	else
	{
		BindToAttributeChanged();
	}
}

void UCCWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UCCAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCCAttributeSet>(AS);
	
	if (!IsASCInitialized())
		return;
	InitializeAttributeDelegate();
}

void UCCWidgetComponent::BindToAttributeChanged()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& pair : AttributeMap)
	{
		BindWidgetToAttributeChange(GetUserWidgetObject(), pair);
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &pair](UWidget* childWidget)
		{
			BindWidgetToAttributeChange(childWidget, pair);
		});
	}
}

void UCCWidgetComponent::BindWidgetToAttributeChange(UWidget* widgetObject,
	const TTuple<FGameplayAttribute, FGameplayAttribute>& pair) const
{
	UCCAttributeWidget* attributeWidget = Cast<UCCAttributeWidget>(widgetObject);
	if (!IsValid(attributeWidget))
		return;
	if (!attributeWidget->MatchesAttribute(pair))
		return;
		
	attributeWidget->OnAttributeChanged(pair, AttributeSet.Get());// for initial value
		
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Key).AddLambda([this, attributeWidget, &pair](const FOnAttributeChangeData&)
	{
		attributeWidget->OnAttributeChanged(pair, AttributeSet.Get());
	});
}
