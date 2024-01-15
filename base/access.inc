<?php

	namespace Base;

	abstract class Access {
		const PERMISSION_UNDEFINED		= 'undefined';
		const PERMISSION_YES			= 'yes';
		const PERMISSION_NO				= 'no';

		private static array $accesses = [];
		private static array $superUsers = [];
		private static array $usersRights = [];
		private static array $groupsRights = [];

		public static string | null $userId = null;
		public static int | null $userGroup = null;

		public static function SetUserData(?int $userId, ?int $userGroup): void {
			self::$userId = $userId;
			self::$userGroup = $userGroup;
		}

		public static function AddCollection(int $id, string $name, string $title = ''): void {
			self::$accesses[$id] = ['name' => $name, 'title' => $title, 'rights' => []];
		}

		public static function AddRight(int $collection, int $id, string $name, $title = ''): void {
			self::$accesses[$collection]['rights'][] = ['id' => $id, 'name' => $name, 'title' => $title];
		}

		public static function GetRights(): array {
			return self::$accesses;
		}

		public static function RegSuperUsers(array $users): void {
			self::$superUsers = $users;
		}

		public static function SetGroupsRights(array $rights): void {
			self::$groupsRights = $rights;
		}

		public static function SetUsersRights(array $rights): void {
			self::$usersRights = $rights;
		}

		public static function Allows(array $rights, int $collection, int $instance): bool {
			if (!isset(self::$userId) || !isset(self::$userGroup)) return false;
			if (in_array(self::$userId, self::$superUsers)) return true;
			foreach ($rights as $right) if (self::Allow($right, $collection, $instance)) return true;
			return false;
		}

		public static function Allow(int $right, int $collection, int $instance = 0): bool {
			if (!isset(self::$userId) || !isset(self::$userGroup)) return false;
			if (in_array(self::$userId, self::$superUsers)) return true;
			switch (self::AllowUser($right, self::$userId, $collection, $instance)) {
				case self::PERMISSION_YES: return true;
				case self::PERMISSION_NO: return false;
			}
			if (self::AllowGroup($right, self::$userGroup, $collection, $instance) == self::PERMISSION_YES) return true;
			return false;
		}

		private static function AllowGroup(int $right, int $group, int $collection, int $instance): string {
			if ($instance && isset(self::$groupsRights[$group][$collection][$instance][$right])) return self::$groupsRights[$group][$collection][$instance][$right];
			if (!isset(self::$groupsRights[$group][$collection][0][$right])) return self::PERMISSION_UNDEFINED;
			return self::$groupsRights[$group][$collection][0][$right];
		}

		private static function AllowUser(int $right, int $user, int $collection, int $instance): string {
			if ($instance && isset(self::$usersRights[$user][$collection][$instance][$right])) return self::$usersRights[$user][$collection][$instance][$right];
			if (!isset(self::$usersRights[$user][$collection][0][$right])) return self::PERMISSION_UNDEFINED;
			return self::$usersRights[$user][$collection][0][$right];
		}

	}