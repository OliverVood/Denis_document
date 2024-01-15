<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Model;

	class AccessGroups extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {  }

		public function GetAccessGroup(int $gid): array {
			$result = $this->table->Select(null, "(`gid` = {$gid}) AND (instance = 0)");
			return $this->table->FetchAll($result, function(& $items, $item) {
				$items[$item['collection']][$item['right']] = $item['permission'];
			});
		}

		public function UpdateAccess(array $items, int $gid): void {
			$values = [];
			foreach ($items as $collection => $rights) {
				foreach ($rights as $right => $permission) {
					$values[] = "({$gid}, {$collection}, {$right}, '{$permission}')";
				}
			}
			$this->table->Delete("`gid` = {$gid}");
			if ($values) $this->table->Query("INSERT INTO `{$this->table->GetName()}` (`gid`, `collection`, `right`, `permission`) VALUES " . implode(', ', $values));
		}
	}