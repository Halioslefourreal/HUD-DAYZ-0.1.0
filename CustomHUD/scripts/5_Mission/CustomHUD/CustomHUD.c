class CustomHUD
{
	protected Widget m_Root;

	protected TextWidget m_HealthValue;
	protected TextWidget m_BloodValue;
	protected TextWidget m_WaterValue;
	protected TextWidget m_EnergyValue;

	protected ProgressBarWidget m_HealthBar;
	protected ProgressBarWidget m_BloodBar;
	protected ProgressBarWidget m_WaterBar;
	protected ProgressBarWidget m_EnergyBar;

	protected float m_UpdateTimer;

	void CustomHUD()
	{
		m_Root = GetGame().GetWorkspace().CreateWidgets("CustomHUD/HUD/hud_stats.layout");

		if (!m_Root)
		{
			ErrorEx("CustomHUD: impossible de charger CustomHUD/HUD/hud_stats.layout", ErrorExSeverity.WARNING);
			return;
		}

		m_HealthValue = TextWidget.Cast(m_Root.FindAnyWidget("CustomHudHealthValue"));
		m_BloodValue = TextWidget.Cast(m_Root.FindAnyWidget("CustomHudBloodValue"));
		m_WaterValue = TextWidget.Cast(m_Root.FindAnyWidget("CustomHudWaterValue"));
		m_EnergyValue = TextWidget.Cast(m_Root.FindAnyWidget("CustomHudEnergyValue"));

		m_HealthBar = ProgressBarWidget.Cast(m_Root.FindAnyWidget("CustomHudHealthBar"));
		m_BloodBar = ProgressBarWidget.Cast(m_Root.FindAnyWidget("CustomHudBloodBar"));
		m_WaterBar = ProgressBarWidget.Cast(m_Root.FindAnyWidget("CustomHudWaterBar"));
		m_EnergyBar = ProgressBarWidget.Cast(m_Root.FindAnyWidget("CustomHudEnergyBar"));
	}

	void ~CustomHUD()
	{
		if (m_Root)
		{
			m_Root.Unlink();
			m_Root = null;
		}
	}

	void Update(PlayerBase player, float timeslice)
	{
		if (!m_Root)
			return;

		m_UpdateTimer += timeslice;

		if (m_UpdateTimer < 0.25)
			return;

		m_UpdateTimer = 0;

		if (!player || !player.IsAlive())
		{
			m_Root.Show(false);
			return;
		}

		m_Root.Show(true);

		float health = GetRatio(player.GetHealth("GlobalHealth", "Health"), player.GetMaxHealth("GlobalHealth", "Health"));
		float blood = GetRatio(player.GetHealth("GlobalHealth", "Blood"), player.GetMaxHealth("GlobalHealth", "Blood"));
		float water = GetStatRatio(player.GetStatWater());
		float energy = GetStatRatio(player.GetStatEnergy());

		if (m_HealthBar)
			m_HealthBar.SetCurrent(health);

		if (m_BloodBar)
			m_BloodBar.SetCurrent(blood);

		if (m_WaterBar)
			m_WaterBar.SetCurrent(water);

		if (m_EnergyBar)
			m_EnergyBar.SetCurrent(energy);

		if (m_HealthValue)
			m_HealthValue.SetText(ToPercent(health));

		if (m_BloodValue)
			m_BloodValue.SetText(ToPercent(blood));

		if (m_WaterValue)
			m_WaterValue.SetText(ToPercent(water));

		if (m_EnergyValue)
			m_EnergyValue.SetText(ToPercent(energy));
	}

	protected float GetRatio(float value, float max)
	{
		if (max <= 0)
			return 0;

		return Math.Clamp(value / max, 0, 1);
	}

	protected float GetStatRatio(PlayerStatBase stat)
	{
		if (!stat || stat.GetMax() <= 0)
			return 0;

		return Math.Clamp(stat.Get() / stat.GetMax(), 0, 1);
	}

	protected string ToPercent(float ratio)
	{
		return Math.Round(ratio * 100).ToString() + " %";
	}
};
