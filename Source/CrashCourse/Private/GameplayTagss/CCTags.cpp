


#include "GameplayTagss/CCTags.h"

namespace CCTags
{
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG(Primary, "CCTags.CCAbilities.Primary");
		UE_DEFINE_GAMEPLAY_TAG(SecondAbility, "CCTags.CCAbilities.SecondAbility");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ThirdAbility, "CCTags.CCAbilities.ThirdAbility", "nothing need to be know");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActiveOnGiveAbility, "CCTags.CCAbilities.ActiveOnGiveAbility", "tag for ability activate on give");
	}
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG(HitReact, "CCTags.Events.HitReact");
		}
	}
}