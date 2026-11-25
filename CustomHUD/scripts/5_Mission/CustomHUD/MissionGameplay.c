modded class MissionGameplay
{
	protected ref CustomHUD m_CustomHUD;

	void MissionGameplay()
	{
		m_CustomHUD = new CustomHUD();
	}

	void ~MissionGameplay()
	{
		m_CustomHUD = null;
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		if (m_CustomHUD)
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			m_CustomHUD.Update(player, timeslice);
		}
	}
};
