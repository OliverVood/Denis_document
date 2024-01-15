<?php

	namespace Proj\Admin\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;

	class Composition extends Model {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

		public function CreateUnit(array $data): void {
			$sampleConsts = file_get_contents(__DIR__ . '/samples/consts.sample');

			$unitName = strtolower($data['name']);
			$unitDir = DIR_UNITS . $unitName . '/';

			$replace = [];
			$replace['<sample>'] = $unitName;
			$replace['<Sample>'] = ucfirst(strtolower($data['name']));
			$replace['<SAMPLE>'] = strtoupper($data['name']);

			$prepareConsts = [
				'[TITLE]'									=> $data['title']
			];

			$sampleConsts = str_replace(array_keys($prepareConsts), $prepareConsts, $sampleConsts);
			$sampleConsts = str_replace(array_keys($replace), $replace, $sampleConsts);
			$this->WriteFile($unitDir, "{$unitName}.consts.inc", $sampleConsts);

			foreach ($data['routes'] as $route => ['binds' => $binds]) {
				$routeDir = $unitDir . $route . '/';

				$replace['[route]'] = strtolower($route);
				$replace['[Route]'] = ucfirst(strtolower($route));

				$prepareController = [
					'[REQUIRE]'								=> "require DIR_UNITS . '<sample>/<sample>.consts.inc';",
					'[REQUIRE_MODEL]'						=> '',
					'[USE]'									=> $route === Consts\Composition::ROUTE_ADMIN ? 'Base\UnitAccess' : 'Base\Unit',
					'[USE_CONSTS]'							=> "\n\tuse Proj\Units\Consts;",
					'[USE_MODEL]'							=> '',
					'[PROPERTY_MODEL]'						=> '',
					'[EXTENDS]'								=> $route === Consts\Composition::ROUTE_ADMIN ? 'UnitAccess' : 'Unit',
					'[IMPLEMENTS]'							=> ' implements Consts\<Sample>',
					'[PARAM_ID]'							=> 'self::ID, ',
					'[PARAM_NAME]'							=> 'self::NAME, ',
					'[PARAM_TITLE]'							=> 'self::TITLE, ',
					'[INSTANCE_MODEL]'						=> ''
				];
				if ($binds & Consts\Composition::FILE_ACTIONS) {
					$prepareController['[REQUIRE]']			= "require DIR_UNITS . '<sample>/[route]/<sample>.actions.inc';";
					$prepareController['[USE]']				= 'Proj\[Route]\Actions';
					$prepareController['[USE_CONSTS]']		= '';
					$prepareController['[EXTENDS]']			= 'Actions\<Sample>';
					$prepareController['[IMPLEMENTS]']		= '';
					$prepareController['[PARAM_ID]']		= '';
					$prepareController['[PARAM_NAME]']		= '';
					$prepareController['[PARAM_TITLE]']		= '';

					$prepareActions = [
						'[USE]'								=> $route === Consts\Composition::ROUTE_ADMIN ? 'Base\UnitAccess' : 'Base\Unit',
						'[EXTENDS]'							=> $route === Consts\Composition::ROUTE_ADMIN ? 'UnitAccess' : 'Unit',
					];
					$sampleActions = file_get_contents(__DIR__ . '/samples/actions.sample');
					$sampleActions = str_replace(array_keys($prepareActions), $prepareActions, $sampleActions);
					$sampleActions = str_replace(array_keys($replace), $replace, $sampleActions);
					$this->WriteFile($routeDir, "{$unitName}.actions.inc", $sampleActions);
				}
				if ($binds & Consts\Composition::FILE_STRUCTURE) {
					$prepareController['[REQUIRE]']			= "require DIR_UNITS . '<sample>/[route]/<sample>.structure.inc';";
					$prepareController['[USE]']				= 'Proj\[Route]\Structure';
					$prepareController['[USE_CONSTS]']		= '';
					$prepareController['[EXTENDS]']			= 'Structure\<Sample>';
					$prepareController['[IMPLEMENTS]']		= '';
					$prepareController['[PARAM_ID]']		= '';
					$prepareController['[PARAM_NAME]']		= '';
					$prepareController['[PARAM_TITLE]']		= '';

					$prepareStructure = [
						'[REQUIRE]'							=> "require DIR_UNITS . '<sample>/<sample>.consts.inc';",
						'[USE_UNIT]'						=> "\n\tuse Base\UnitAccess;",
						'[USE_CONSTS]'						=> "\n\tuse Proj\Units\Consts;",
						'[USE_ACTIONS]'						=> '',
						'[EXTENDS]'							=> 'UnitAccess implements Consts\<Sample>',
						'[PARAM_ID]'						=> 'self::ID, ',
						'[PARAM_NAME]'						=> 'self::NAME, ',
						'[PARAM_TITLE]'						=> 'self::TITLE, '
					];

					if ($binds & Consts\Composition::FILE_ACTIONS) {
						$prepareStructure['[REQUIRE]']		= "require DIR_UNITS . '<sample>/[route]/<sample>.actions.inc';";
						$prepareStructure['[USE_UNIT]']	= '';
						$prepareStructure['[USE_CONSTS]']	= '';
						$prepareStructure['[USE_ACTIONS]']	= "\n\tuse Proj\[Route]\Actions;";
						$prepareStructure['[EXTENDS]']		= 'Actions\<Sample>';
						$prepareStructure['[PARAM_ID]']		= '';
						$prepareStructure['[PARAM_NAME]']	= '';
						$prepareStructure['[PARAM_TITLE]']	= '';
					}

					$sampleStructure = file_get_contents(__DIR__ . '/samples/structure.sample');
					$sampleStructure = str_replace(array_keys($prepareStructure), $prepareStructure, $sampleStructure);
					$sampleStructure = str_replace(array_keys($replace), $replace, $sampleStructure);
					$this->WriteFile($routeDir, "{$unitName}.structure.inc", $sampleStructure);
				}
				if ($binds & Consts\Composition::FILE_MODEL) {
					$prepareController['[REQUIRE_MODEL]']	= "\n\trequire DIR_UNITS . '<sample>/[route]/<sample>.model.inc';";
					$prepareController['[USE_MODEL]']		= "\n\tuse Proj\[Route]\Model;";
					$prepareController['[PROPERTY_MODEL]']	= "\n\n\t\t" . 'private Model\<Sample> $model;';
					$prepareController['[INSTANCE_MODEL]']	= "\n\n\t\t\t" . '$this->model = Model\<Sample>::instance();';

					$sampleModel = file_get_contents(__DIR__ . '/samples/model.sample');
					$sampleModel = str_replace(array_keys($replace), $replace, $sampleModel);
					$this->WriteFile($routeDir, "{$unitName}.model.inc", $sampleModel);
				}

				$sampleController = file_get_contents(__DIR__ . '/samples/controller.sample');
				$sampleController = str_replace(array_keys($prepareController), $prepareController, $sampleController);
				$sampleController = str_replace(array_keys($replace), $replace, $sampleController);
				$this->WriteFile($routeDir, "{$unitName}.controller.inc", $sampleController);

				$file = fopen(DIR_UNITS . "{$replace['[route]']}.units.inc", 'a');
				fwrite($file, "\n\trequire DIR_UNITS . '{$unitName}/{$replace['[route]']}/{$unitName}.controller.inc';");
				fclose($file);
			}

			$file = fopen(DIR_UNITS . 'consts.inc', 'a');
			fwrite($file, "\n\tconst ID_{$replace['<SAMPLE>']} = {$data['id']};");
			fclose($file);
		}

		public function CreateModel(string $name, string $unitName, string $routeName): void {
			$replace = [
				'[Route]' => ucfirst(strtolower($routeName)),
				'<Sample>' => ucfirst(strtolower($name))
			];
			$sampleModel = file_get_contents(__DIR__ . '/samples/model.sample');
			$sampleModel = str_replace(array_keys($replace), $replace, $sampleModel);
			$this->WriteFile(DIR_UNITS . "{$unitName}/{$routeName}/", "{$name}.model.inc", $sampleModel);
		}

		public function CreateEditor(string $name, string $unitName): void {
			$replace = [
				'<sample>' => strtolower($name),
				'<Sample>' => ucfirst(strtolower($name)),
				'[unit]' => strtolower($unitName)
			];

			$sampleEditor = file_get_contents(__DIR__ . '/samples/editor.sample');
			$sampleEditor = str_replace(array_keys($replace), $replace, $sampleEditor);
			$this->WriteFile(DIR_UNITS . "{$unitName}/admin/editors/{$replace['<sample>']}/", "{$replace['<sample>']}.editor.inc", $sampleEditor);

			$sampleEditorModel = file_get_contents(__DIR__ . '/samples/editor.model.sample');
			$sampleEditorModel = str_replace(array_keys($replace), $replace, $sampleEditorModel);
			$this->WriteFile(DIR_UNITS . "{$unitName}/admin/editors/{$replace['<sample>']}/", "{$replace['<sample>']}.editor.model.inc", $sampleEditorModel);
		}

		private function WriteFile(string $path, string $name, string $content) {
			if (!is_dir($path)) mkdir($path, 0777, true);
			file_put_contents($path . $name, $content);
		}

	}

	Composition::init();