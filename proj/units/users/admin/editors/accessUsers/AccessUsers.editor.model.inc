<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Model;

	class AccessUsers extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {  }

		public function GetAccessUser(int $uid): array {
			$result = $this->table->Select(null, "(`uid` = {$uid}) AND (instance = 0)");
			return $this->table->FetchAll($result, function(& $items, $item) {
				$items[$item['collection']][$item['right']] = $item['permission'];
			});
		}

		public function UpdateAccess(array $items, int $uid): void {
			$values = [];
			foreach ($items as $collection => $rights) {
				foreach ($rights as $right => $permission) {
					$values[] = "({$uid}, {$collection}, {$right}, '{$permission}')";
				}
			}
			$this->table->Delete("`uid` = {$uid}");
			if ($values) $this->table->Query("INSERT INTO `{$this->table->GetName()}` (`uid`, `collection`, `right`, `permission`) VALUES " . implode(', ', $values));
		}
	}