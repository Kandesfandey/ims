import React from "react";
import DashboardIcon from "@mui/icons-material/Dashboard";
import PersonOutlineIcon from "@mui/icons-material/PersonOutline";
import CreditCardIcon from "@mui/icons-material/CreditCard";

import { Link } from "react-router-dom";
import {
  SidebarContainer,
  TopContainer,
  LinkContainer,
  Logo,
  Divider,
  CenterContainer,
  UnorderedList,
  Title,
  ListElement,
  SpanContainer,
  LocalShippingIcon,
  SettingsApplicationsIcon,
  InsertChartIcon,
  NotificationsNoneIcon,
  AccountCircleOutlinedIcon,
  ExitToAppIcon,
  StoreIcon,
} from "./styles/sidebar";

const SideBar = () => {
  return (
    <SidebarContainer>
      <TopContainer>
        <LinkContainer to="/">
          <Logo>lamadmin</Logo>
        </LinkContainer>
      </TopContainer>
      <Divider />
      <CenterContainer>
        <UnorderedList>
          <Title>MAIN</Title>
          <ListElement>
            <DashboardIcon className="icon" />
            <SpanContainer>Dashboard</SpanContainer>
          </ListElement>
          <Title>LISTS</Title>
          <Link to="/users" style={{ textDecoration: "none" }}>
            <ListElement>
              <PersonOutlineIcon className="icon" />
              <SpanContainer>Users</SpanContainer>
            </ListElement>
          </Link>
          <Link to="/products" style={{ textDecoration: "none" }}>
            <ListElement>
              <StoreIcon />
              <SpanContainer>Products</SpanContainer>
            </ListElement>
          </Link>
          <ListElement>
            <CreditCardIcon className="icon" />
            <SpanContainer>Request</SpanContainer>
          </ListElement>
          <ListElement>
            <LocalShippingIcon />
            <SpanContainer>Delivery</SpanContainer>
          </ListElement>
          <Title>USEFUL</Title>
          <ListElement>
            <InsertChartIcon className="icon" />
            <SpanContainer>Stats</SpanContainer>
          </ListElement>
          <ListElement>
            <NotificationsNoneIcon />
            <SpanContainer>Notifications</SpanContainer>
          </ListElement>
          <ListElement>
            <SettingsApplicationsIcon />
            <SpanContainer>Settings</SpanContainer>
          </ListElement>
          <Title>USER</Title>
          <ListElement>
            <AccountCircleOutlinedIcon />
            <SpanContainer>Profile</SpanContainer>
          </ListElement>
          <ListElement>
            <ExitToAppIcon />
            <SpanContainer>Logout</SpanContainer>
          </ListElement>
        </UnorderedList>
      </CenterContainer>
    </SidebarContainer>
  );
};

export default SideBar;
