#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void Init() {}
	virtual void End()	{}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// �t�F�[�h�֘A
	void UpdateFade();
	void DrawFade() const;

	bool IsFadingIn() const;	// �t�F�[�h�C����
	bool IsFadingOut() const;	// �t�F�[�h�A�E�g��
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }	// �t�F�[�h�C��or�A�E�g��

	void StartFadeOut();	// �t�F�[�h�A�E�g�J�n

	/// <summary>
	/// �t�F�[�h�̖��邳���擾
	/// </summary>
	/// <returns>0(�t�F�[�h���Ă��Ȃ�)�`255(�^����)</returns>
	int GetFadeBright() const { return m_fadeBright; }

private:
	// �t�F�[�h�֘A����
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;
};