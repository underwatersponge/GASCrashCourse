


#include "GameplayTagss/CCTags.h"

namespace CCTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG(Projectile, "CCTags.SetByCaller.Projectile");
	}
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG(Primary, "CCTags.CCAbilities.Primary");
		UE_DEFINE_GAMEPLAY_TAG(SecondAbility, "CCTags.CCAbilities.SecondAbility");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ThirdAbility, "CCTags.CCAbilities.ThirdAbility", "nothing need to be know");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActiveOnGiveAbility, "CCTags.CCAbilities.ActiveOnGiveAbility", "tag for ability activate on give");
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG(Attack, "CCTags.CCAbilities.Enemy.Attack");
		}
	}
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "CCTags.Events.KillScored", "tag for kill scored");
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG(Death, "CCTags.Events.Player.Death");
			UE_DEFINE_GAMEPLAY_TAG(HitReact, "CCTags.Events.Player.HitReact");
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG(HitReact, "CCTags.Events.HitReact");
			UE_DEFINE_GAMEPLAY_TAG(EndAttack, "CCTags.Events.Enemy.EndAttack");
			UE_DEFINE_GAMEPLAY_TAG(MeleeTraceHit, "CCTags.Events.Enemy.MeleeTraceHit");
		}
	}
}