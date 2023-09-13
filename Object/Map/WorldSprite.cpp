#include "WorldSprite.h"

/// <summary>
/// ������
/// </summary>
/// <param name="textureGraph">�e�N�X�`���̉摜�n���h��</param>
/// <param name="chipPixelSize">�X�v���C�g�̂P�`�b�v�̃s�N�Z���T�C�Y</param>
/// <param name="spriteNo">�X�v���C�g�ԍ�</param>
void WorldSprite::Init(int textureGraph, int chipPixelSize, int spriteNo)
{
	this->m_hGraph = textureGraph;

    // NOTE:���������ɌŒ肵�Ă��邪�A�ύX��������Ύ����Ŋ֐���ǉ�����K�v������
    // �S���_����uv�f�[�^��ݒ�
    int texW, texH;
    GetGraphTextureSize(textureGraph, &texW, &texH);
    const int chipNum = texW / chipPixelSize;
    const int chipNoX = spriteNo % chipNum;
    const int chipNoY = spriteNo / chipNum;
    // �e�N�X�`���S����1.0�Ƃ�������cihp��ɑ΂���uv�̃T�C�Y
    const float oneChipUVRate = 1.0f / static_cast<float>(chipNum);   
    m_vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
    m_vertex[0].v = (chipNoY + 0.0f) * oneChipUVRate;
    m_vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
    m_vertex[1].v = (chipNoY + 0.0f) * oneChipUVRate;
    m_vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
    m_vertex[2].v = (chipNoY + 1.0f) * oneChipUVRate;
    m_vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
    m_vertex[3].v = (chipNoY + 1.0f) * oneChipUVRate;

    // �f�B�t���[�Y�A�X�y�L�����͏��������ɌŒ�
    for (int i = 0; i < 4; i++)
    {
        m_vertex[i].dif = GetColorU8(255, 255, 255, 255);
        m_vertex[i].spc = GetColorU8(0, 0, 0, 0);
        // ��]���T�|�[�g���Ȃ��̂Ńm�[�}�����Œ�
        m_vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);   

        // �⏕�e�N�X�`�����T�|�[�g���Ȃ��̂�uv�Œ�
        m_vertex[i].su = 0.0f;
        m_vertex[i].sv = 0.0f;
    }

    // �Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
    m_index[0] = 0;
    m_index[1] = 1;
    m_index[2] = 2;
    m_index[3] = 3;
    m_index[4] = 2;
    m_index[5] = 1;
}

/// <summary>
/// �T�C�Y�ƃ|�W�V�����ɉ����ĂS���_���̒��_�ʒu�𒲐�
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="chipSize">�z�u���郏�[���h�X�v���C�g�̃T�C�Y</param>
void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
    // �s�{�b�g���S�Őݒ�
    // ����
    m_vertex[0].pos = VScale(VGet(-1.0f, 0.0f, 1.0f), spriteSize * 0.5f);
    // �E��
    m_vertex[1].pos = VScale(VGet(1.0f,  0.0f, 1.0f), spriteSize * 0.5f);
    // ����
    m_vertex[2].pos = VScale(VGet(-1.0,  0.0f, -1.0f), spriteSize * 0.5f);
    // �E��
    m_vertex[3].pos = VScale(VGet(1.0f,  0.0f, -1.0f), spriteSize * 0.5f);

    // ���W�𒆐S�ɂ���
    for (int i = 0; i < 4; i++)
    {
        m_vertex[i].pos = VAdd(m_vertex[i].pos, pos);
    }
}

// �`��
void WorldSprite::Draw()
{
    // �Q�|���S���̕`��
    DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_hGraph, true);
}