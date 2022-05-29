import styled from 'styled-components/macro'
import { LanguageOutlined } from "@mui/icons-material";
// import FullscreenExitOutlinedIcon from "@mui/icons-material/FullscreenExitOutlined";
// import NotificationsNoneOutlinedIcon from "@mui/icons-material/NotificationsNoneOutlined";
// import ChatBubbleOutlineOutlinedIcon from "@mui/icons-material/ChatBubbleOutlineOutlined";
// import ListOutlinedIcon from "@mui/icons-material/ListOutlined";

export const NavbarContainer = styled.div`
  height: 50px;
  border-bottom: 0.5px solid rgb(231, 228, 228);
  display: flex;
  align-items: center;
  font-size: 14px;
  color: #555;
`
export const WrapperContainer = styled.div`
  width: 100%;
  padding: 20px;
  display: flex;
  align-items: center;
  justify-content: space-between;
`
export const SearchContainer = styled.div`
  display: flex;
  align-items: center;
  border: 0.5px solid lightgray;
  padding: 3px;
`

export const InputContainer = styled.input`
  border: none;
  outline: none;
  background: transparent;
  &::placeholder {
    font-size: 12px;
  }
`
export const ItemsContainer = styled.div`
  display: flex;
  align-items: center;
`
export const ItemContainer = styled.div`
  display: flex;
  align-items: center;
  margin-right: 20px;
  position: relative;
`

export const LanguageOutlinedIcon = styled(LanguageOutlined)`
  font-size: 20px;
`
// export const FullscreenExitOutlinedIconContainer = styled(FullscreenExitOutlinedIcon)`
//   font-size: 20px;
// `
// export const NotificationsNoneOutlinedIconContainer = styled(NotificationsNoneOutlinedIcon)`
//   font-size: 20px;
// `
// export const ChatBubbleOutlineOutlinedIconContainer = styled(ChatBubbleOutlineOutlinedIcon)`
//   font-size: 20px;
// `
// export const ListOutlinedIconContainer = styled(ListOutlinedIcon)`
//   font-size: 20px;
// `

export const AvatarContainer = styled.div`
  width: 30px;
  height: 30px;
  border-radius: 50%;
`

export const CounterContainer = styled.img`
  width: 15px;
  height: 15px;
  background-color: red;
  border-radius: 50%;
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 10px;
  font-weight: bold;
  position: absolute;
  top: -5px;
  right: -5px;
`