//struct PS_INPUT
//{
//	float4 Diffuse         : COLOR0 ;
//	float4 Specular        : COLOR1 ;
//	float2 TexCoords0      : TEXCOORD0 ;
//	float2 TexCoords1      : TEXCOORD1 ;
//} ;

//struct PS_OUTPUT
//{
//	float4 Output          : COLOR0 ;
//} ;

//sampler sampler0 : register( s0 ) ;

//PS_OUTPUT main( PS_INPUT psin )
//{
//	PS_OUTPUT psout ;
//	float4 texc ;

//	texc  = tex2D( sampler0, psin.TexCoords0 ) ; 

//	psout.Output.r = texc.b ;
//	psout.Output.g = texc.g ;
//	psout.Output.b = texc.r ;
//	psout.Output.a = texc.a ;

//	return psout ;
//}

sampler sampler0 : register(s0);

float mosLv; //  モザイク強さ 0.0に近いほど荒い
float alpha; //  輝度：0.0～1.0

float4 main(float2 uv : TEXCOORD0) : COLOR0
{
    bool isR = false;
    bool isG = false;
    bool isB = false;
    bool isA = false;
    
    float size1 = mosLv * 100;
     //  0.5fで中心揃えになる、端の部分が半分になるイメージ
    float2 uv1 = floor(uv * size1 + 0.5f) / size1;

    float4 texc = tex2D(sampler0, uv1);
    
    return texc;
}
