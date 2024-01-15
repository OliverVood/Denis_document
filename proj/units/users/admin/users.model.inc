<?php

	namespace Proj\Admin\Model;

	use Base\Access;
	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Users extends Model {
		use Instance;

		private static bool $login = false;

		private static string | null $id = null;
		private static string | null $group = null;
		private static string | null $alias = null;

		private DBObject $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBObject::instance();

			$this->CheckSession();
			if ($this->IsLogin()) $this->UpdateAccess();
		}

		public function Auth(string $login, string $password): bool {
			$login = $this->db->Escaping($login);
			$hash = $this->PasswordHash($password);

			$data = $this->db->SelectOne(Consts\Users::TABLES['users'], ['id', 'gid', 'login', 'password'], "`login` = '{$login}' AND `password` = '{$hash}'");

			if (!$data) return false;

			$this->Login($data);

			return true;
		}

		public function PasswordHash($pass): string {
			return md5($pass);
		}

		private function Login(array $data): void {
			self::$login = true;

			self::$id = $data['id'];
			self::$group = $data['gid'];
			self::$alias = $data['login'];

			$this->UpdateSession();
			$this->UpdateAccess();
		}

		public function Logout(): void {
			self::$id = null;
			self::$group = null;
			self::$alias = null;

			self::$login = false;

			$this->UpdateSession();
			$this->UpdateAccess();
		}

		public function IsLogin(): bool {
			return self::$login;
		}

		private function UpdateSession(): void {
			$_SESSION['ADMIN']['USER']['LOGIN'] = self::$login;

			$_SESSION['ADMIN']['USER']['ID'] = self::$id;
			$_SESSION['ADMIN']['USER']['GROUP'] = self::$group;
			$_SESSION['ADMIN']['USER']['ALIAS'] = self::$alias;
		}

		private function CheckSession(): void {
			if (isset($_SESSION['ADMIN']['USER'])) {
				self::$login = $_SESSION['ADMIN']['USER']['LOGIN'] ?? false;

				self::$id = $_SESSION['ADMIN']['USER']['ID'] ?? false;
				self::$group = $_SESSION['ADMIN']['USER']['GROUP'] ?? false;
				self::$alias = $_SESSION['ADMIN']['USER']['ALIAS'] ?? false;
			}
		}

		private function UpdateAccess(): void {
			Access::SetUserData(self::$id, self::$group);

			Access::RegSuperUsers(SUPER_USERS);

			$result = $this->db->Select(Consts\Users::TABLES['access_groups']);
			$groupsRights = $this->db->FetchAll($result, function (& $items, $item) {
				$items[$item['gid']][$item['collection']][$item['instance']][$item['right']] = $item['permission'];
			});
			Access::SetGroupsRights($groupsRights);

			$result = $this->db->Select(Consts\Users::TABLES['access_users']);
			$usersRights = $this->db->FetchAll($result, function (& $items, $item) {
				$items[$item['uid']][$item['collection']][$item['instance']][$item['right']] = $item['permission'];
			});
			Access::SetUsersRights($usersRights);
		}

		public function GetAlias(): string {
			return self::$alias ?? '';
		}

		public function GetListGroups(): array {
			$result = $this->db->Select(Consts\Users::TABLES['groups'], ['id', 'name'], '`state` = ' . Consts\Users::STATE_GROUP_ACTIVE, 'datecr');
			return $this->db->FetchAll($result, function(& $items, $item) {
				$items[$item['id']] = $item['name'];
			});
		}

	}

	Users::init();