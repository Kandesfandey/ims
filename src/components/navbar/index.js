import React, { useContext } from "react";
import SearchOutlinedIcon from "@mui/icons-material/SearchOutlined";
import LanguageOutlinedIcon from "@mui/icons-material/LanguageOutlined";
import FullscreenExitOutlinedIcon from "@mui/icons-material/FullscreenExitOutlined";
import NotificationsNoneOutlinedIcon from "@mui/icons-material/NotificationsNoneOutlined";
import ChatBubbleOutlineOutlinedIcon from "@mui/icons-material/ChatBubbleOutlineOutlined";
import ListOutlinedIcon from "@mui/icons-material/ListOutlined";
import { InputContainer, ItemsContainer, NavbarContainer, SearchContainer, WrapperContainer, ItemContainer } from "./styles";

const Navbar = () => {
  return (
    <NavbarContainer>
      <WrapperContainer>
        <SearchContainer>
          <InputContainer type="text" placeholder="Search..." />
          <SearchOutlinedIcon />
        </SearchContainer>
        <ItemsContainer>
          <ItemContainer>
            <LanguageOutlinedIcon className="icon" />
            English
          </ItemContainer>

          <ItemContainer>
            <FullscreenExitOutlinedIcon className="icon" />
          </ItemContainer>
          <ItemContainer>
            <NotificationsNoneOutlinedIcon className="icon" />
            <div className="counter">1</div>
          </ItemContainer>
          <ItemContainer>
            <ChatBubbleOutlineOutlinedIcon className="icon" />
            <div className="counter">2</div>
          </ItemContainer>
          <ItemContainer>
            <ListOutlinedIcon className="icon" />
          </ItemContainer>
          <ItemContainer>
            <img
              src="https://images.pexels.com/photos/941693/pexels-photo-941693.jpeg?auto=compress&cs=tinysrgb&dpr=2&w=500"
              alt=""
              className="avatar"
            />
          </ItemContainer>
        </ItemsContainer>
      </WrapperContainer>
    </NavbarContainer>
  );
};

export default Navbar;
