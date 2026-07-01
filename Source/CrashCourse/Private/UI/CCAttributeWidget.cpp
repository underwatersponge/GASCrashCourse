// 


#include "UI/CCAttributeWidget.h"

void UCCAttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, const UCCAttributeSet* AttributeSet,float oldValue)
{
	const float attributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float maxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);
	
	BP_OnAttributeChange(attributeValue, maxAttributeValue, oldValue);
}

bool UCCAttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
