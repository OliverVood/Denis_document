<?php

	namespace Base\Editor;

	use Base\DB\Select;
	use Base\DB\Table;

	class Model {
		protected Table $table;
		protected Select $querySelect;

		public function __construct(Table $table) {
			$this->table = $table;

			$this->querySelect = new Select();
			$this->querySelect->calc('*')->table($this->table->GetName());
		}

		protected function SelectData(int $page_current = 1, int $page_entries = 0): array {
			$query = $this->querySelect->get();

			$ext = [];
			if ($page_entries) {
//				$page_current = GetInt('page', 1);
				$start = ($page_current - 1) * $page_entries;
				$result = $this->table->Query("SELECT COUNT(*) AS `count` FROM ({$query}) AS `table`");
				$page_records = $this->table->Fetch($result)['count'];

				$ext['page'] = [
					'records' => $page_records,
					'current' => $page_current,
					'count' => (int)ceil($page_records / $page_entries)
				];
				$query = $this->querySelect->limit($start, $page_entries)->get();
			}

			$result = $this->table->Query($query);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			return [$items, $ext];
		}

		public function GetItem(int $id): array {
			return $this->table->SelectOne(null, "(`id` = {$id})");
		}

		public function GetState(int $id): int {
			return (int)$this->table->SelectOneField('state', "`id` = {$id}");
		}

		public function Create(array $data): void {
			$this->table->Insert($data);
		}

		public function Update(array $data, int $id): void {
			$this->table->Update($data, "`id` = {$id}");
		}

		public function Delete(int $id): void {
			$this->table->Update(['state' => 100], "`id` = {$id}");
		}

	}