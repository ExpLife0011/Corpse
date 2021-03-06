#pragma once

namespace DuiLib
{
	#define ADDRESS_IPV4		4		//IPv4��ַʹ�õ����ݸ���
	
	class UILIB_API CIPAddressUI : public CHorizontalLayoutUI
	{
		public:
			CIPAddressUI();
			/*~CIPAddressUI();*/

		public:
			virtual LPCTSTR GetClass() const;
			virtual LPVOID GetInterface(LPCTSTR pstrName);
			virtual UINT GetControlFlags() const;
			virtual void DoEvent(TEventUI& event);
			virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
			virtual void SetText(LPCTSTR pstrText);
			virtual CDuiString GetText() const;
			virtual void SetFont(int iFont);
			virtual void PaintStatusImage(HDC hDC);
		public:
			bool IsBlank();
		protected:
			bool DoEvent(LPVOID lParam);
			bool OnNotify(LPVOID lParam);

			void SetNormalImage(LPCTSTR lpszNormalImage);
			void SetHotImage(LPCTSTR lpszHotImage);
			void SetFocusedImage(LPCTSTR lpszFocusedImage);
			void SetDisabledImage(LPCTSTR lpszDisabledImage);

			bool IsSendNotify();
			void SetSendNotify(bool bSendNotify);
		protected:
			CRichEditUI* m_pBlock[ADDRESS_IPV4];
			UINT m_nButtonState;
			int m_iFont;
			bool m_bSendNotify;

			CDuiString m_sNormalImage;			//�༭����ͨ״̬ͼƬ
			CDuiString m_sFocusedImage;			//�༭���ȡ����״̬ͼƬ
			CDuiString m_sHotImage;					
			CDuiString m_sDisabledImage;
	};
}