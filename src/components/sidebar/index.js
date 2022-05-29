import React from "react";

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
  CreditCardIcon,
  PersonOutlineIcon,
  DashboardIcon,
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
          <LinkContainer to="/users">
            <ListElement>
              <PersonOutlineIcon />
              <SpanContainer>Users</SpanContainer>
            </ListElement>
          </LinkContainer>
          <LinkContainer to="/products">
            <ListElement>
              <StoreIcon />
              <SpanContainer>Products</SpanContainer>
            </ListElement>
          </LinkContainer>
          <ListElement>
            <CreditCardIcon />
            <SpanContainer>Request</SpanContainer>
          </ListElement>
          <ListElement>
            <LocalShippingIcon />
            <SpanContainer>Delivery</SpanContainer>
          </ListElement>
          <Title>USEFUL</Title>
          <ListElement>
            <InsertChartIcon />
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
